#include <wiringPi.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "MQTTClient.h"

#define ADDRESS		"test.mosquitto.org:8081"
#define CLIENTID	"ClientPubE"
//#define TOPIC		"IoTSystem"

#define DHT_PIN 25
#define DC_A_PIN 26
#define DC_B_PIN 23
#define LED_PIN 7
#define FLAME_PIN 16
#define SPI_CH 0

#define ADC_CS 29
#define DUST_OUT 4
#define DUST_ADC_CH 3
#define GAS_ADC_CH 4

#define STEPMOTOR_PIN_1A 27
#define STEPMOTOR_PIN_1B 0
#define STEPMOTOR_PIN_2A 1
#define STEPMOTOR_PIN_2B 24
#define US_TRIG 28
#define US_OUT 29
#define PIR_PIN 2
#define LIMIT_PIN 21 // 원래 핀과 숫자 겹쳐서 수정함
#define BUZZER_PIN 14

#define R_LED_PIN 20 // 원래 pin과 숫자 겹쳐서 수정함
#define G_LED_PIN 3
#define B_LED_PIN 4

#define DISTANCE 150;
#define ONE_SECOND 1000;
#define ONE_MINUTE 60000;

//함수 정의
int dht(int k);
int on_dcmotor();
int off_dcmotor();
int detect_gas();
int detect_person();
int soil_moisture();
int dust(int pin, int out);

void edge_flame_rise(void);
void edge_flame_fall(void);

void feeder(); // 사료 지급
bool exist_feed(); // 사료가 존재하는지 확인
bool detcet_pet(); // 반려동물 감지 

int main(int argc, char* argv[]) {
	MQTTClient client;
	MQTTCLient_connectionOptions conn_opts = MQTTClient_connectionOptions_initializer;
	MQTTClient_message pubmsg = MQTTClient_message_initializer;
	MQTTClient_deliveryToken token;
	int rc;

	MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

	if ((rc = MQTTClient_connect, (client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
		printf("Failed to connect, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < 20; i++) {
		int pir = digitalRead(PIR_PIN);
		char msg[5];
		sprintf(msg, "%d", pir);
		pubmsg.payload = msg;
		pubmsg.payloadlen = (int)strlen(msg);
		MQTTClient_publishMessage(client, "GAS_MS" ,&pubmsg, &token);
		//message 
		delay(1000);

	}

	MQTTClient_disconntect(client, 10000);
	MQTTClient_destroy(&client);

	time_t rawTime;
	struct tm* pTimeInfo;

	rawTime = time(NULL);                // 현재 시간을 받음
	pTimeInfo = localtime(&rawTime);    // 현재 시간을 이쁘게 struct tm에 넣음

	printf("time_t : %lld\n", rawTime);

	int detect_time_p = 0; // 반려 동물을 감지한 '시간'
	int time_detect_p = 0; // 반려 동물이 감지된 '횟수'
	int time_feed = 0; // 먹이를 지급한 횟수
	int limit = 0; // 리밋 스위치

	int now_day = pTimeInfo->tm_mday;
	int now_hour = pTimeInfo->tm_hour; // 현재 시간
	int now_min = pTimeInfo->tm_min; 
	int now_sec = pTimeInfo->tm_sec;

	int day = now_day;

	if (day != now_day) { // 날짜가 바뀌면 초기화
		int detect_time_p = 0;
		int time_detect_p = 0; 
		int time_feed = 0;
	}


	if (wiringPiSetup() == -1) return 1;
	if (wiringPiSPISetup() == -1) return -1;

	while (1) {
		pinMode(TOUCH_PIN, INPUT);
		touch = digitalRead(TOUCH_PIN);
		pinMode(LIMIT_PIN, INPUT);
		limit = digitalRead(LIMIT_PIN);

		if (now_hour == 9 || now_hour == 13 || now_hour == 19) {
			feeder();
			time_feed++;
		}

		// 1초에 한 번, 반려 동물이 감지되면 감지 시간 증가
		if (detect_pet()) {
			int detect_time_p++;
			delay(ONE_SECOND);
		}

		// 감지 시간이 10분 이상일 때
		if (detect_time_p >= ONE_MINUTE*10 ) {
			pinMode(LED_PIN, OUTPUT);
			digitalWrite(LED_PIN, HIGH);
			time_detect_p++;
			detect_time_p == 0; //초기화
		}

		// 5회 이상 동물이 감지되거나 밥을 4번 이상 줄 때 LED와 BUZZER가 켜짐
		if (time_detect_p >= 5 || time_feed >= 4) {
			pinMode(LED_PIN, OUTPUT);
			digitalWrite(LED_PIN, HIGH);
			pinMode(BUZZER_PIN, OUTPUT);
			digitalWrite(BUZZER_PIN, HIGH);
			
			time_detect_p = 0; // 초기화
			time_feed = 0;
		}

		// limit스위치를 누르면 led와 buzzer가 꺼짐
		if (limit == 1) {
			pinMode(LED_PIN, OUTPUT);
			digitalWrite(LED_PIN, LOW);
			pinMode(BUZZER_PIN, OUTPUT);
			digitalWrite(BUZZER_PIN, LOW);
		}


		// 아래로 중간 프로젝트
		// 온도 측정
		if (dht(0) > 26) {
			pinMode(G_LED_PIN, OUTPUT);
			digitalWrite(G_LED_PIN, HIGH);
			on_dcmotor();
		}
		else {
			pinMode(G_LED_PIN, OUTPUT);
			digitalWrite(G_LED_PIN, LOW);
		}

		// 습도 측정
		if (dht(1) > 70) {
			pinMode(B_LED_PIN, OUTPUT);
			digitalWrite(B_LED_PIN, HIGH);
			on_dcmotor();
		}
		else {
			pinMode(B_LED_PIN, OUTPUT);
			digitalWrite(B_LED_PIN, LOW);
		}

		// 가스 감지
		if (detect_gas() == 1) {
			pinMode(R_LED_PIN, OUTPUT);
			digitalWrite(R_LED_PIN, HIGH);
		}
		else {
			pinMode(R_LED_PIN, OUTPUT);
			digitalWrite(R_LED_PIN, LOW);
		}

		// 공기질
		if (dust(DUST_ADC_CH, DUST_OUT) > 1000) {
			on_dcmotor();
			pinMode(R_LED_PIN, OUTPUT);
			pinMode(G_LED_PIN, OUTPUT);
			digitalWrite(R_LED_PIN, HIGH);
			digitalWrite(G_LED_PIN, HIGH);
		}
		else {
			pinMode(R_LED_PIN, OUTPUT);
			digitalWrite(R_LED_PIN, LOW);
			pinMode(G_LED_PIN, OUTPUT);
			digitalWrite(G_LED_PIN, LOW);
		}

		// 쾌적한 환경일 경우 fan을 끔
		pinMode(DC_A_PIN, INPUT);
		dcm = digitalRead(DC_A_PIN);
		if (dcm == 1 && dust(DUST_ADC_CH, DUST_OUT) < 1000 && dht(0) < 25 && dht(1) < 50) {
			off_dcmotor();
		}

	}
}

void feeder() { // 먹이를 주기 위해 스텝 모터 활용
	int i;

	pinMode(PIN_1A, OUTPUT);
	pinMode(PIN_1B, OUTPUT);
	pinMode(PIN_2A, OUTPUT);
	pinMode(PIN_2B, OUTPUT);

	for (i = 0; i < 3; i++) {
		digitalWrite(PIN_1A, HIGH);
		digitalWrite(PIN_1B, LOW);
		digitalWrite(PIN_2A, LOW);
		digitalWrite(PIN_2B, LOW);
		usleep(8000);
		digitalWrite(PIN_1A, LOW);
		digitalWrite(PIN_1B, HIGH);
		digitalWrite(PIN_2A, LOW);
		digitalWrite(PIN_2B, LOW);
		usleep(8000);
		digitalWrite(PIN_1A, LOW);
		digitalWrite(PIN_1B, LOW);
		digitalWrite(PIN_2A, HIGH);
		digitalWrite(PIN_2B, LOW);
		usleep(8000);
		digitalWrite(PIN_1A, LOW);
		digitalWrite(PIN_1B, LOW);
		digitalWrite(PIN_2A, LOW);
		digitalWrite(PIN_2B, HIGH);
		usleep(8000);
	}

	for (i = 0; i < 3; i++) {
		digitalWrite(PIN_1A, LOW);
		digitalWrite(PIN_1B, LOW);
		digitalWrite(PIN_2A, LOW);
		digitalWrite(PIN_2B, HIGH);
		usleep(8000);
		digitalWrite(PIN_1A, LOW);
		digitalWrite(PIN_1B, LOW);
		digitalWrite(PIN_2A, HIGH);
		digitalWrite(PIN_2B, LOW);
		usleep(8000);
		digitalWrite(PIN_1A, LOW);
		digitalWrite(PIN_1B, HIGH);
		digitalWrite(PIN_2A, LOW);
		digitalWrite(PIN_2B, LOW);
		usleep(8000);
		digitalWrite(PIN_1A, HIGH);
		digitalWrite(PIN_1B, LOW);
		digitalWrite(PIN_2A, LOW);
		digitalWrite(PIN_2B, LOW);
		usleep(8000);
	}
}

bool exist_feed() { // 초음파 센서로 먹이가 존재하는지 확인 
	int dis;
	long startTime, travelTime;

	if (wiringPiSetup() == -1) return 1;

	pinMode(US_TRIG, OUTPUT);
	pinMode(US_OUT, INPUT);

	digitalWrite(US_TRIG, LOW);
	usleep(2);
	digitalWrite(US_TRIG, HIGH);
	usleep(20);
	digitalWrite(US_TRIG, LOW);
	while (digitalRead(US_OUT) == LOW);
	startTime = micros();
	while (digitalRead(US_OUT) == HIGH);
	travelTime = micros() - startTime;
	dis = travelTime / 58;

	printf("%d", dis);

	if (dis > DISTANCE)
		return false;

	else
		return true;

}


bool detect_pet() { // pir센서로 반려동물이 감지되었는지 확인
	int pir = 0;

	pinMode(PIR_PIN, INPUT);
	pir = digitalRead(PIR_PIN);
	delay(1000);
	if (pir == 1)
		return true;
	else
		return false;
}

//아래로 중간 프로젝트와 동일 
float f_temp;
int dht(int k) {
	delay(80);

	int val[5] = { 0,0,0,0,0 };
	uint8_t lststate = 1;
	uint8_t cnt = 0;
	uint8_t j = 0, i;

	pinMode(DHT_PIN, OUTPUT);
	digitalWrite(DHT_PIN, 0);
	delay(18);
	digitalWrite(DHT_PIN, 1);
	delayMicroseconds(40);

	pinMode(DHT_PIN, INPUT);

	for (i = 0; i < 100; i++) {
		cnt = 0;
		while (digitalRead(DHT_PIN) == lststate) {
			cnt++;
			delayMicroseconds(1);
			if (cnt == 255) break;
		}

		lststate = digitalRead(DHT_PIN);

		if (cnt == 255) break;

		if ((i >= 4) && (i % 2 == 0)) {
			val[j / 8] <<= 1;
			if (cnt > 16) val[j / 8] |= 1;
			j++;
		}
	}

	f_temp = val[2] * 9. / 5. + 32;

	if ((j >= 40) && (val[4] == ((val[0] + val[1] + val[2] + val[3]) & 0xFF))) {
		if (k)
			return val[0];
		else
			return val[2];
	}

	else return -1;
}

int on_dcmotor() {
	pinMode(DC_A_PIN, OUTPUT);
	digitalWrite(DC_A_PIN, 1);
}

int off_dcmotor() {
	pinMode(DC_A_PIN, OUTPUT);
	digitalWrite(DC_A_PIN, 0);
}

int detect_gas() {
	int gas_value = 0;
	unsigned char buf[3];

	pinMode(ADC_CS, OUTPUT);

	buf[0] = 0x06 | ((GAS_ADC_CH & 0x04) >> 2);
	buf[1] = ((GAS_ADC_CH & 0x03) << 6) & 0x07;
	buf[2] = 0x00;

	digitalWrite(ADC_CS, 0);
	wiringPiSPIDataRW(SPI_CH, buf, 3);

	buf[1] = 0x0F & buf[1];

	gas_value = (buf[1] << 8) | buf[2];

	digitalWrite(ADC_CS, 1);

	if (gas_value > 350)
		return 1;
}

int detect_person() {
	int pir;

	pinMode(PIR_PIN, INPUT);
	pir = digitalRead(PIR_PIN);

	return pir;
}

int dust(int pin, int out) {
	int value = 0;
	unsigned char buf[3];

	pinMode(pin, OUTPUT);
	pinMode(out, OUTPUT);

	digitalWrite(out, LOW);
	delayMicroseconds(280);

	buf[0] = 0x06 | ((DUST_ADC_CH & 0x04) >> 2);
	buf[1] = ((DUST_ADC_CH & 0x03) << 6);
	buf[2] = 0x00;
	digitalWrite(ADC_CS, 0);
	wiringPiSPIDataRW(SPI_CH, buf, 3);
	buf[1] = 0x0F & buf[1];
	value = (buf[1] << 8) | buf[2];
	digitalWrite(ADC_CS, 1);

	delayMicroseconds(40);
	digitalWrite(out, HIGH);
	delayMicroseconds(9680);

	return value;
}

void edge_flame_rise(void) {
	pinMode(R_LED_PIN, OUTPUT);
	digitalWrite(R_LED_PIN, HIGH);
	wiringPiISR(FLAME_PIN, INT_EDGE_RISING, edge_flame_fall);
	printf("Flame_Edge_Rised\n");
}

void edge_flame_fall(void) {
	pinMode(R_LED_PIN, OUTPUT);
	digitalWrite(R_LED_PIN, LOW);
	wiringPiISR(FLAME_PIN, INT_EDGE_FALLING, edge_flame_rise);
	printf("Flame_Edge_Falled\n");
}