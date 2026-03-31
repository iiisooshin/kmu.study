function Event() {

    function handleOnClick(e) {
        console.log(e);
        console.log(e.target.textContent);
        alert(e.target.textContent + " 버튼을 클릭했습니다.");
    }
   

    return(
        <div>
            <button onClick={handleOnClick}>Click</button>
            <button onClick={() => {alert("버튼을 클릭했습니다.")}}>Click</button>
        </div>
    );
}


export default Event;