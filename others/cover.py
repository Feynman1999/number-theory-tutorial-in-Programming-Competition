import cv2
import numpy as np
from math import sqrt

def isPrime(n):
    if n <= 1:
        return False
    for i in range(2, long long(sqrt(n) + 1)):
        if n % i == 0:
            return False
    return True

height = 1024
width = 1024

one_num_size = 32
color_non_prime = 255 * np.ones((one_num_size,one_num_size,3), np.int8)
color_prime = np.zeros((one_num_size,one_num_size,3), np.int8)

img = np.zeros((height,width,3), np.uint8)

num  = 0

for i in range(height//one_num_size):
    for j in range(width//one_num_size):
        num = num + 1
        left_up_corner_index_h = i*one_num_size
        left_up_corner_index_w = j*one_num_size
        if isPrime(num):
            img[left_up_corner_index_h:left_up_corner_index_h+one_num_size, left_up_corner_index_w:left_up_corner_index_w+one_num_size,:]  = color_prime
        else:
            img[left_up_corner_index_h:left_up_corner_index_h+one_num_size, left_up_corner_index_w:left_up_corner_index_w+one_num_size,:]  = color_non_prime

# print(color_non_prime.shape, img.shape)
cv2.imwrite("prime.jpg", img)

