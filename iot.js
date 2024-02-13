function XHR_write(data){
        var xhr = new XMLHttpRequest();

        xhr.open("GET","remote_con.php?" + data);
        xhr.send();
}

function XHR_read(data){
        var xhr = new XMLHttpRequest();

        xhr.open("GET","remote_con.php?" + data, false);
        xhr.send();
		
	return xhr.responseText;
}


function repeat(){
	EXISTFEED(); TIMEFEED(); STAYTIME(); TLS(); TEMP(); HUMI(); FLAME(); DUST(); GAS(); 
}
setInterval(function(){repeat();},500);

//--------------------------------------------------------//

function FEED(){
	XHR_write('FEED_MS');
}


function DCMON(){
	XHR_write('DCMON');
	
	document.DCM.src='img/dcm_on.png';
}

function DCMOFF(){
	XHR_write('DCMOFF');
	
	document.DCM.src='img/dcm_off.png';
}

function ALARMOFF(){
	XHR_write('ALARMOFF');
	
	document.TLS.src='img/no_too_stay_long.png';
}

function TIMEFEED(){
	var val=XHR_read('TIMEFEED');
	if(val != -1){
		document.getElementById("TF_val").value=val;
	}
	
}

function STAYTIME(){
	var val=XHR_read('STAYTIME');
	if(val != -1){
		document.getElementById("ST_val").value=val;
	}
}

function TLS(){
	var val=XHR_read('TLS');

	if(val==1){
		document.TLS.src='img/too_long_stay.png';
	}else{
		document.TLS.src='img/no_too_stay_long.png';
	}
}

function EXISTFEED(){
	var val = XHR_read('EXISTFEED');
	if(val==1){
		document.TLS.src='img/exist_feed.png';
	}else{
		document.TLS.src='img/no_exist_feed.png';
	}
}


function TEMP(){
	var val=XHR_read('TEMP');
	
	if(val!=-1){
		document.TEMPOV.style.opacity=0.5-((parseInt(val)+50)/80*0.5);
		
		document.getElementById("TEMP_val").value=val+"'C";
	}
}	

function HUMI(){
	var val=XHR_read('HUMI');
	
	if(val!=-1){
		document.HUMIOV.style.opacity=val/100*0.5;
		
		document.getElementById("HUMI_val").value=val+"%";
	}
}	

function FLAME(){
	var val=XHR_read('FLAME');
	
	if(val==1){
		document.FLAME.src='img/flame_on.png';
	}else{
		document.FLAME.src='img/flame_off.png';
	}
}

function GAS(){
	var val=XHR_read('GAS');

	document.GAS.style.opacity=(parseInt(val)/4095)*0.8+0.2;
	document.getElementById("GAS_val").value=val;
}


function DUST(){
	var val=XHR_read('DUST');

	document.DUST.style.opacity=(parseInt(val)/4095)*0.8+0.2;
	document.getElementById("DUST_val").value=val;
}