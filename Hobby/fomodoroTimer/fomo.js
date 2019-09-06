const clockTime = document.querySelector('h1');
const startClock = document.querySelector('#start');
const endClock = document.querySelector('#end');
const main = document.querySelector('.main');
const body = document.querySelector('body');

minute = 0;
seconds = 0;

function secondPlus(){
    seconds++;

    if (seconds === 60){
        minute++;
        seconds = 0;
        
        if(minute === 25){
            timerBye();
        }
    }
}

function timerBye(){
    alert('End')
    stopTimer();
}

function stopTimer(){
    clockTime.innerText = `00 : 00`;
    clearInterval(clicked);
    clockTime.style.color = 'black';
    body.style.backgroundColor='white';
}
function getTime(){
    secondPlus();
    clockTime.innerText = `${minute < 10 ? `0${minute}` : minute} : ${
        seconds < 10 ? `0${seconds}` : seconds}`
}

//function init(){
//    setInterval(getTime, 1000);
//}

startClock.onclick = function(){
    clicked = setInterval(getTime,1000);
    clockTime.style.color = 'white';
    body.style.backgroundColor = 'black';
}

endClock.onclick = function(){
    stopTimer();
}