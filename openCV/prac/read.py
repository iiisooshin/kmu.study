import cv2 as cv


# image read
img = cv.imread('Photos/cat.jpeg')

cv.imshow('Cat', img)


cv.waitKey(0)




# video read

# capture = cv.VideoCapture('Videos/cat.mp4')

# while True:
#     isTrue, frame = capture.read()
#     cv.imshow('Video', frame)

#     if cv.waitKey(20) & 0xFF==ord('d'):
#         break

# capture.release()
# cv.destroyAllWindows()
