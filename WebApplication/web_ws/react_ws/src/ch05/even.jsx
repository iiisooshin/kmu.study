// import React, {useState} from "react";

function Even(props) {
        return(
            <div>
                {props.number % 2 === 0 ? "짝수" : "홀수"}
            </div>
        );
    }

export default Even;