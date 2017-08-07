DESCRIPTION = "Enlightenment image" 

inherit core-image 


IMAGE_LINGUAS += " ja-jp "

IMAGE_FEATURES += "splash package-management x11-base" 

#Enlightenment
IMAGE_INSTALL  += " enlightenment enlightenment-session \
                    enlightenment-config-mobile \
                    enlightenment-backgrounds \
                    elementary elementary-configs elementary-themes \
                  "

IMAGE_INSTALL  += " udev-extraconf " 

#IMAGE_INSTALL += "midori takao-fonts mpv jack2" 


