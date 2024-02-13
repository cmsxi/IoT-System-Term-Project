<?php
	if(isset($_GET['LEDON'])){
		$value = shell_exec("/home/pi/PHP_LEDON");
		echo $value;
	}else if(isset($_GET['LEDOFF'])){
		$value = shell_exec("/home/pi/PHP_LEDOFF");
		echo $value;
	}else if(isset($_GET['PIR'])){
                $value = shell_exec("/home/pi/PHP_PIR");
                echo $value;
	}else if(isset($_GET['SOUND'])){
                $value = shell_exec("/home/pi/PHP_SOUND");
                echo $value;
	}else if(isset($_GET['BUZZERON'])){
                $value = shell_exec("/home/pi/PHP_BUZZERON");
                echo $value;
	}else if(isset($_GET['BUZZEROFF'])){
                $value = shell_exec("/home/pi/PHP_BUZZEROFF");
                echo $value;
	}else if(isset($_GET['DCMON'])){
                $value = shell_exec("/home/pi/PHP_DCMON");
                echo $value;
	}else if(isset($_GET['DCMOFF'])){
                $value = shell_exec("/home/pi/PHP_DCMOFF");
                echo $value;
	}else if(isset($_GET['STMON'])){
                $value = shell_exec("/home/pi/PHP_STMON");
                echo $value;
	}else if(isset($_GET['SW'])){
                $value = shell_exec("/home/pi/PHP_SW");
                echo $value;
	}else if(isset($_GET['LIGHT'])){
                $value = shell_exec("/home/pi/PHP_LIGHT");
                echo $value;
	}else if(isset($_GET['US'])){
                $value = shell_exec("/home/pi/PHP_US");
                echo $value;
	}else if(isset($_GET['TEMP'])){
                $value = shell_exec("/home/pi/PHP_TEMP");
                echo $value;
	}else if(isset($_GET['HUMI'])){
                $value = shell_exec("/home/pi/PHP_HUMI");
                echo $value;
	}else if(isset($_GET['VR'])){
                $value = shell_exec("/home/pi/PHP_VR");
                echo $value;
	}else if(isset($_GET['TOUCH'])){
                $value = shell_exec("/home/pi/PHP_TOUCH");
                echo $value;
	}else if(isset($_GET['PD'])){
                $value = shell_exec("/home/pi/PHP_PD");
                echo $value;
	}else if(isset($_GET['BUMP'])){
                $value = shell_exec("/home/pi/PHP_BUMP");
                echo $value;
	}else if(isset($_GET['IRO'])){
                $value = shell_exec("/home/pi/PHP_IRO");
                echo $value;
	}else if(isset($_GET['LASERON'])){
                $value = shell_exec("/home/pi/PHP_LASERON");
                echo $value;
	}else if(isset($_GET['LASEROFF'])){
                $value = shell_exec("/home/pi/PHP_LASEROFF");
                echo $value;
	}else if(isset($_GET['MERC'])){
                $value = shell_exec("/home/pi/PHP_MERC");
                echo $value;
	}else if(isset($_GET['TILT'])){
                $value = shell_exec("/home/pi/PHP_TILT");
                echo $value;
	}else if(isset($_GET['FLAME'])){
                $value = shell_exec("/home/pi/PHP_FLAME");
                echo $value;
	}else if(isset($_GET['REED'])){
                $value = shell_exec("/home/pi/PHP_REED");
                echo $value;
	}else if(isset($_GET['REDON'])){
                $value = shell_exec("/home/pi/PHP_REDON");
                echo $value;
        }else if(isset($_GET['REDOFF'])){
                $value = shell_exec("/home/pi/PHP_REDOFF");
                echo $value;
        }else if(isset($_GET['GREENON'])){
                $value = shell_exec("/home/pi/PHP_GREENON");
                echo $value;
        }else if(isset($_GET['GREENOFF'])){
                $value = shell_exec("/home/pi/PHP_GREENOFF");
                echo $value;
        }else if(isset($_GET['BLUEON'])){
                $value = shell_exec("/home/pi/PHP_BLUEON");
                echo $value;
        }else if(isset($_GET['BLUEOFF'])){
                $value = shell_exec("/home/pi/PHP_BLUEOFF");
                echo $value;
        }else if(isset($_GET['RELAYON'])){
                $value = shell_exec("/home/pi/PHP_RELAYON");
                echo $value;
        }else if(isset($_GET['RELAYOFF'])){
                $value = shell_exec("/home/pi/PHP_RELAYOFF");
                echo $value;
        }else if(isset($_GET['IRT'])){
                $value = shell_exec("/home/pi/PHP_IRT");
                echo $value;
        }else if(isset($_GET['LIMIT'])){
                $value = shell_exec("/home/pi/PHP_LIMIT");
                echo $value;
        }else if(isset($_GET['KNOCK'])){
                $value = shell_exec("/home/pi/PHP_KNOCK");
                echo $value;
        }else if(isset($_GET['DUST'])){
                $value = shell_exec("/home/pi/PHP_DUST");
                echo $value;
        }else if(isset($_GET['SM'])){
                $value = shell_exec("/home/pi/PHP_SM");
                echo $value;
        }else if(isset($_GET['GAS'])){
                $value = shell_exec("/home/pi/PHP_GAS");
                echo $value;
        }else if(isset($_GET['THERM'])){
                $value = shell_exec("/home/pi/PHP_THERM");
                echo $value;
        }else if(isset($_GET['AT'])){
                $value = shell_exec("/home/pi/PHP_AT");
                echo $value;
        }

?>
