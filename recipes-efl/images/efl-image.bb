DESCRIPTION = "Enlightenment image" 

inherit core-image 


IMAGE_FEATURES += "splash package-management x11-base" 

#Enlightenment
IMAGE_INSTALL  += " enlightenment enlightenment-config-mobile \
                    enlightenment-backgrounds \
                  "

IMAGE_INSTALL  += " udev-extraconf " 

#IMAGE_INSTALL += "midori takao-fonts mpv jack2" 


