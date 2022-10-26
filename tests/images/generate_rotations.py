# This script generates a set of rotated images from an input image
# usage: python genera_rotations.py <input_file> <max_angle> <num_rotations>
# example: python generate_rotations.py images/cdc/1.png 40 10
import sys
import os
import cv2
import numpy as np


def rotate_image(image, angle):
    height, width = image.shape[:2] 
    image_center = (width/2, height/2) 

    rotation_image = cv2.getRotationMatrix2D(image_center, angle, 1.)
    abs_cos = abs(rotation_image[0,0]) 
    abs_sin = abs(rotation_image[0,1])

    bound_w = int(height * abs_sin + width * abs_cos)
    bound_h = int(height * abs_cos + width * abs_sin)

    rotation_image[0, 2] += bound_w/2 - image_center[0]
    rotation_image[1, 2] += bound_h/2 - image_center[1]

    rotated_image = cv2.warpAffine(image, rotation_image, (bound_w, bound_h))
    return rotated_image
    

def main():
    if len(sys.argv) != 4:
        print("usage: python generate_rotations.py <input_file> <max_angle> <num_rotations>")
        sys.exit(1)
    input_file = sys.argv[1]
    max_angle = int(sys.argv[2])
    num_rotations = int(sys.argv[3])

    image = cv2.imread(input_file)
    image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    output_name = os.path.splitext(input_file)[0]
    for angle in range(-max_angle, max_angle+1, 2*max_angle//num_rotations):
        if angle == 0:
            continue
        rotated_image = rotate_image(image, angle)
        cv2.imwrite(output_name + "_rotated(" + str(angle) + ").png", rotated_image)


if __name__ == '__main__':
    main()
