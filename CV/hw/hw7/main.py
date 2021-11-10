import cv2
from matplotlib import pyplot as plt

img = cv2.imread('finger_print.png',0)

plt.hist(img.ravel(), 256, [0,256]); 
plt.show()