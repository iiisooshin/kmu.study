import React from 'react';
import ReactDOM from 'react-dom/client';
import './index.css';
// import App from './App';
// import Header from './ch03/header';
// import Library from './ch03/library';
import Clock from './ch04/clock';

// const element = <h1>Hello World!</h1>

// function Clock(prop){
//   return(
//       <div>
//         <h1>현재 시간</h1>
//         <h2>{new Date().toLocaleTimeString()}</h2>
//       </div>
//   );
// }

// function ClockSeoul(){
//   return(
//     <div>
//       <h1>Seoul Time:</h1>
//       <h2>{new Date().toLocaleTimeString("ko-KR", {timeZone:"Asia/Seoul"})}</h2>
//     </div>
    
//   ); 
// }

// function ClockTokyo(){
//   return(
//     <div>
//       <h1>Tokyo Time:</h1>
//       <h2>{new Date().toLocaleTimeString("ja-JP", {timeZone:"Asia/Tokyo"})}</h2>
//     </div>
//   );
// }

// function ClockNewyork(){
//   return(
//     <div>
//       <h1>Newyork Time:</h1>
//       <h2>{new Date().toLocaleTimeString("en-US", {timeZone:"America/New_York"})}</h2>
//     </div>
    
//   );
// }




function ButtonLogin() {
  return (
    <button type='button' onClick={() => alert("hi")}>
      Login
    </button>
  );
}

function ButtonSignup() {
  return (
    <button>
      Signup
    </button>
  );
}

function ButtonContact() {
  return (
    <button>
      Contact
    </button>
  );
}




const root = ReactDOM.createRoot(document.getElementById('root'));


// 1초마다 element 렌더링
setInterval(() => {
  // element 생성 매 1초마
  root.render(
    // <Clock />
    // <div>
    //   <ClockSeoul />
    //   <ClockTokyo />
    //   <ClockNewyork />
    // </div>

    <div>
      <ButtonLogin />
      <ButtonSignup />
      <ButtonContact />
    </div>

  );

}, 1000);