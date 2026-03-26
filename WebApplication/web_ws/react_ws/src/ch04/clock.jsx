function Clock(props){
  return(
      <div>
        <h1>{props.location} 현재 시간</h1>
        <h2>{new Date().toLocaleTimeString()}</h2>
      </div>
  );
}


export default Clock;