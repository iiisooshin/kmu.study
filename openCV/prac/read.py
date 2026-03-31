import cv2 as cv


# image read
# img = cv.imread('Photos/cat.jpeg')

# cv.imshow('Cat', img)


# cv.waitKey(0)




# video read

capture = cv.VideoCapture(0)

while True:
    isTrue, frame = capture.read()
    
    # 추가된 부분: 프레임을 제대로 못 읽어오면 루프 종료
    if not isTrue:
        print("웹캠에서 영상을 가져올 수 없습니다. 카메라 권한을 확인해 주세요.")
        break

    cv.imshow('Video', frame)

    if cv.waitKey(20) & 0xFF==ord('d'):
        break

capture.release()
cv.destroyAllWindows()