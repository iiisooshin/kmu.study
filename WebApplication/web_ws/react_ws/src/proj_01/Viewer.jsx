import React from "react";

function Viewer(props) {

    return(
        <div>
            <div>현재 카운트 : </div>
            <h1>{props.count}</h1>
        </div>
    );
};


export default Viewer;