const body = document.querySelector('body');

const IMG_NUMBER = 5;

function handleImgLoad(){
    console.log("finished loading");
}

function paintImage(imageNumber){
    const image = new Image();
    image.src = `images/${imageNumber + 1}.jpg`;
    image.classList.add("bgImage");
    body.appendChild(image);
}

function getRandom(){
    const number = Math.floor(Math.random() * IMG_NUMBER);
    return Math.floor(number);
}

function init(){
    const randomnNumber = getRandom();
    paintImage(randomnNumber);
}

init();