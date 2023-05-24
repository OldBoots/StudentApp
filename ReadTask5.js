function getRandomInt(max){
    return Math.floor(Math.random() * max);
}

function removeAllClass(className){
    var temp = document.getElementsByClassName(className);
    while(temp.length > 0){
        temp[0].parentNode.removeChild(temp[0]);
    }
}

function setLineEdit(){
    var temp = document.getElementsByClassName("pbody");
    for(let i = 0, input_id = num_quest; i < temp.length; i++, input_id++){
        temp[i].innerHTML += "Ответ: <input type=\"number\" id=\"tusk" + input_id + "\">";
    }
}

function showSolution(){
    var temp = document.getElementsByClassName("solution");
    for(let i = 0; i < temp.length; i++){
        temp[i].setAttribute("style", "clear: both; display: block;");
    }
}

function removeAllTag(tagName){
    var temp = document.getElementsByTagName(tagName);
    while(temp.length > 0){
        temp[0].parentNode.removeChild(temp[0]);
    }
}

var count = ~count~;
var num_quest = ~quest~;

function doSomething(){
    var mas_main_div = document.getElementsByClassName("prob_maindiv");
    var ex = "";
    var temp_tusk;
    removeAllTag("a");
    removeAllClass("outer_number");
    removeAllClass("briefcase");

    for(let i = 0; i < count;){
        temp_tusk = mas_main_div[getRandomInt(mas_main_div.length)];
        if(/\d/.test(temp_tusk.querySelector(".answer").querySelector("span").innerHTML)){
            ex += temp_tusk.innerHTML
            i++;
        }
    }
    document.head.innerHTML = "";
    document.body.innerHTML = "";
    document.body.innerHTML += ex;
    for(let j = 0; j < count; j++){
        document.getElementsByClassName("prob_nums")[j].textContent = "№ " + (num_quest + j + 1) + " - Тип 8";
    }
    setLineEdit();
    return document.body.innerHTML;
}; doSomething();
