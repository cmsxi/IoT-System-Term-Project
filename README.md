## IoT System Term Project [2021년 IoT시스템 과목 진행 프로젝트]
라즈베리파이와 웹페이지를 통해 원격으로 "반려동물의 사료 지급, 건강 관리 및 주변 환경 케어"가 가능한 IoT 시스템 프로젝트를 진행하였습니다.

|웹 구성 화면1|웹 구성 화면 2|
|----|----|
|![스크린샷 2024-02-13 155755](https://github.com/cmsxi/IoT-System-Term-Project/assets/133588297/b6c0b015-f224-49fb-9e32-c999fbaa0ec8)|![스크린샷 2024-02-13 155828](https://github.com/cmsxi/IoT-System-Term-Project/assets/133588297/62507257-538b-459f-bb33-324d00780c37)|


라즈베리파이는 한백전자에서 제공하는 카탈로그의 오픈소스를 활용하여 시스템을 활용할 수 있도록 코드를 작성하였습니다.

-------------

### Propose an IoT project
This application provides feed to pets according to the set time. And it can send the information of the meal to the smartphone application. Even if it's not at a fixed time, it's also possible to give a meal right away through the smartphone application. If the amount of feed is less than 20% of the whole container, it is informed through the application and the feeding machine.

#### Motivation
More households have pets than before, but most of them are single-person households. It is difficult for busy office workers to feed their pets with the right amount of food on time. For this reason, many people worry about the distribution of meals for animals staying at home. I came to think of these applications to make sure that such people can give their pets meals even when they are away from home, and that they can check whether they eat or not and how much food they feed.

#### Background
In order to proceed with this project, I need to know the information about what time it will give meals to the pets. And depending on the type of pet, the feed payment time and the amount of feed should vary.

#### Services provided by the proposed project
The service shows information about whether the pet ate food through a smartphone application. This allows a person who has a pet to provide a proper meal to a single pet at home. In addition, the application has a function to provide information on what nutrients are included in various feeds. Since user can enter the pet's health status through an application, it has a function to recommend feed that is appropriate for the pet's health condition. And depending on the type of feed user currently provide to the pet, analyze how well the pet eat the feed and record preference. This allows users to select feed that is suitable for the health of their pets and that is appropriate for their tastes.

#### List of IoT devices.
DC motor, IR obstacle, Touch sensor, RGB LED, etc

IR obstacle detects how much feed is in the feed store. The feed store cle can detect how much food is in the feed store. Depending on the amount of feed that exists in the feed store, RGB RED shows green, yellow, and red colors depending on the amount. When the time is set, the feed is paid by different operating hours depending on the amount paid through the DC motor. It is also possible to manually feed through touch sensor.
