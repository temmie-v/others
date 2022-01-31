import os
import cv2
import numpy as np
import scipy.ndimage as ndimage
import pandas as pd
import matplotlib.pyplot as plt

file_path = input('Enter filepath : ')
# like... 'sample.bmp' or 'C:\Users\...\sample.bmp'
basename = os.path.splitext(os.path.basename(file_path))[0]

print('Reading...')
img = cv2.imread(file_path, 1)
h, w, c = img.shape
scale = 3
img_resize = cv2.resize(img, (w * scale, h * scale))

print('Processing...')
img_gray = cv2.cvtColor(img_resize, cv2.COLOR_BGR2GRAY)
img_blur = cv2.GaussianBlur(img_gray, (5, 5), 0)
r, dst = cv2.threshold(img_blur, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
kernel = np.ones((3, 3), np.uint8)
dst = cv2.dilate(dst, kernel, iterations=1)
cv2.imwrite(basename + '_thresholds.jpg', dst)

print('Detecting boundaries...')
contours, _ = cv2.findContours(dst.astype(
    np.uint8), cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
img_contour = cv2.drawContours(img_resize, contours, -1, (0, 0, 255), 1)
cv2.imwrite(basename + '_counter.jpg', img_contour)

print('Calculating area...')
Areas = []
with open(basename + '_data.csv', 'w') as f:
    for i, contour in enumerate(contours):
        area = cv2.contourArea(contour)  # pixel
        Areas.append(area)
        M = cv2.moments(contour)
        cx = int(M["m10"] / M["m00"])
        cy = int(M["m01"] / M["m00"])
        perimeter = cv2.arcLength(contours[i], True)
        img2 = cv2.drawContours(img_resize, contours, i, (0, 0, 255), 3)
        cv2.putText(img2, str('{:.1f}'.format(area)), (cx, cy),
                    cv2.FONT_HERSHEY_PLAIN,
                    3,
                    (0, 0, 0),
                    2,
                    cv2.LINE_AA)
        if i == (len(contours)-1):
            img2_resize = cv2.resize(img2, (w, h))
            cv2.imwrite(basename + '_' + str(i) + '.jpg', img2_resize)
        if i == 0:
            my_columns_list = [
                'ID', 'Area', 'x_center_of_gravity', 'y_center_of_gravity', 'Perimeter']
            my_columns_str = ','.join(my_columns_list)
            f.write(my_columns_str + '\n')
        else:
            my_data_list = [str(i), str(area), str(cx),
                            str(cy), str(perimeter)]
            my_data_str = ','.join(my_data_list)
            f.write(my_data_str + '\n')

Area_sum = sum(Areas)

print('Exporting data...')
df = pd.read_csv(basename + '_data.csv')
df[r'Area[%]'] = df['Area'] / Area_sum * 100
df.to_csv(basename + '_data_2.csv')

print('Drawing graph...')
radius = list(map(lambda x: (x / 3.1415) ** 0.5 * 2 / 9, Areas))
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
ax.hist(radius, bins=60, range=(0, 12), log=True)
ax.set_title('Grain Size Distribution')
ax.set_xlabel('Diameter [μm]')
ax.set_ylabel('Freq [counts]')

fig.savefig(basename + '_result.png', dpi=600)

print('Done.')