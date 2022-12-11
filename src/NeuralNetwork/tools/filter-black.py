import cv2
import os
import shutil

# get images
images = os.listdir('./')
os.mkdir('./black')

images = filter(lambda x: x.endswith('.png'), images)

for image in images:
    img = cv2.imread(image)
    
    mean = cv2.mean(img)
    if mean[0] < 10 and mean[1] < 10 and mean[2] < 10:
        shutil.move(image, './black/')
