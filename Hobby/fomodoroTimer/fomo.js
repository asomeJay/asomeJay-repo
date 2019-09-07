const clockTime = document.querySelector('h1');
const startClock = document.querySelector('#start');
const endClock = document.querySelector('#end');
const pauseClock = document.querySelector('#pause');
const main = document.querySelector('.main');
const body = document.querySelector('body');
const h5 = document.querySelector('h5');

let time = 0;     // work time과 break time을 번갈아가면서?
const workT = 1;
const breakT = 1;
var overlap = false;
var breakTimerOn = false;
var minute = 0;
var seconds = 0;
var audio = new Audio('start.mp3');

function init(){
    minute = 0;
    seconds = 0;
    breakTimerOn = false;
    overlap = false;
    h5.style.display = 'none';
    clockTime.style.color = 'black';
    body.style.backgroundColor='white';
    printTimer();
}

function secondPlus(objectMinutes){
    seconds++;

    if (seconds === 60){
        minute++;
        seconds = 0;

        if (minute === objectMinutes){
            timerBye();
        }
    }
}

function timerBye(){
    clearInterval(clicked);

    if (h5.style.display === 'none'){
        breakTimerOn = false;
        audio.play();
        alert('잠시 쉬자');

        breakTime();
    }   
    else if (h5.style.display === 'block'){
        breakTimerOn = true;
        overlap = false;
        audio.play();
        alert('공부 하자');
        audio.pause();
        audio.currentTime = 0;
        minute = 0;
        seconds = 0;
        start();
    }
}

function stopTimer(){
    init();
    clearInterval(clicked);
}

function getTime(){
    secondPlus(time);
    printTimer();
}

function timeGo(){
    clicked = setInterval(getTime, 1000);
}

function start(){
    if (overlap === false){
        h5.style.display = 'none';
        time = workT;
        timeGo();
        overlap = true;
        clockTime.style.color = 'white';
        body.style.backgroundColor = 'black';
    }
}

function pause(){
    clearInterval(clicked);
    overlap = false;
}

function end(){
    init();
    clearInterval(clicked);
    body.style.backgroundColor = 'white';
    clockTime.innerText = `00 : 00`;
    clockTime.style.color = 'black';
}

function breakTime(){
    init();
    audio.pause();
    audio.currentTime = 0;
    timeGo();
    h5.style.display = 'block';
    printTimer();
}

function printTimer(){
    clockTime.innerText = `${minute < 10 ? `0${minute}` : minute} : ${
        seconds < 10 ? `0${seconds}` : seconds}`
}

init();
startClock.addEventListener('click', start);
endClock.addEventListener('click', end);
pauseClock.addEventListener('click', pause);
