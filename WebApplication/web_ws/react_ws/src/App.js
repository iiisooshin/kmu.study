import './App.css';
import React from 'react';

function App() {

  let myName = 'iiisoo';

  return (
    // React.createElement('h1', null, '안녕하세요')

    <div className="App">
      <h1>안녕하세요</h1>
      <h2>{myName}입니다.</h2>
    </div>

  );
}

export default App;
