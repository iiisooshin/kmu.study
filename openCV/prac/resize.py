import cv2 as cv



def rescaleFrame(frame, scale=0.2):
    width = int(frame.shape[1] * scale)      # 1 = height
    height = int(frame.shape[0] * scale)     # 0 = width
    dimensions = (width, height)

    return cv.resize(frame, dimensions, interpolation=cv.INTER_AREA)




# img resize

img = cv.imread('Photos/cat.jpeg')
resized_img = rescaleFrame(img)

cv.imshow('Image', img)
cv.imshow('Image Resized', resized_img)

cv.waitKey(0)





# video resize

# capture = cv.VideoCapture('Videos/cat.mp4')

# while True:
#     isTrue, frame = capture.read()

#     frame_resized = rescaleFrame(frame)

#     cv.imshow('Video', frame)
#     cv.imshow('Video Resized', frame_resized)

#     if cv.waitKey(20) & 0xFF==ord('d'):
#         break

# capture.release()
# cv.destroyAllWindows()
