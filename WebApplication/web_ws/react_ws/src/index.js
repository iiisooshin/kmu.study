import React from 'react';
import ReactDOM from 'react-dom/client';
import './index.css';
// import App from './App';
// import Header from './ch03/header';
// import Library from './ch03/library';
// import Clock from './ch04/clock';
// import Header from './ch04/header';
// import Product from './ch04/product';
// import Event from './ch05/event';
// import Counter from './ch05/counter';
// import Counter2 from './ch05/counter2';
// import InputText from './ch05/inputText';
// import InputReset from './ch05/inputReset';
// import NumberOnly from './ch05/numberOnly';
// import CountUseref from './ch05/CountUseref';
// import SearchUseref from './ch05/SearchUseref';
import App from './proj_01/App';



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




// function ButtonLogin() {
//   return (
//     <button onClick={() => alert("Login 클릭")}>
//       Login
//     </button>
//   );
// }

// function ButtonSignup() {
//   return (
//     <button>
//       Signup
//     </button>
//   );
// }

// function ButtonContact() {
//   return (
//     <button>
//       Contact
//     </button>
//   );
// }


// const HeaderProps = {
//   name: '김요한',
//   age: '30'
// };

const root = ReactDOM.createRoot(document.getElementById('root'));


// 1초마다 element 렌더링
// setInterval(() => {
  // element 생성 매 1초마다
  root.render(
      // <Clock />
      // <div>
      //   <ClockSeoul />
      //   <ClockTokyo />
      //   <ClockNewyork />
      // </div>

    // <div>
    //   <ButtonLogin />
    //   <ButtonSignup />
    //   <ButtonContact />
    // </div>
    // <div>
    //   {/* <Header name='신이수' age={25}></Header>
    //   <Header {...HeaderProps}></Header>
    //   <Clock location='대구광역시'></Clock>
    //   <Clock location='부산광역시'></Clock>
    //   <Clock location='서울특별시'></Clock> */}
    //   <Product name='사과' price={1000}></Product>
    //   <Product name='바나나' price={2000}></Product>
    //   <Product name='딸기' price={3000}></Product>
    // </div>


      // <Event></Event>

      // <Counter></Counter>
      // <Counter2></Counter2>

      // <InputText></InputText>
      // <InputReset></InputReset>
      // <NumberOnly></NumberOnly>

      // <CountUseref></CountUseref>
      // <SearchUseref></SearchUseref>

      <App></App>
    
  );

// }, 1000);