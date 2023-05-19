function getRandomInt(max){
    return Math.floor(Math.random() * max);
}

function removeAllClass(className){
    var temp = document.getElementsByClassName(className);
    while(temp.length > 0){
        temp[0].parentNode.removeChild(temp[0]);
    }
}

function simbolHTML(text) {
  var textArea = document.createElement('textarea');
  textArea.innerHTML = text;
  return textArea.value;
}

function setLineEdit(){
    var temp = document.getElementsByTagName("td");
    for(let i = 0, input_name = num_quest, input_id = 0;  i < temp.length; i++){
        if(temp[i].innerHTML === simbolHTML('&#8239;')){
            temp[i].innerHTML = "<input type=\"text\" class=\"table_field\" name=\"tusk_name_" + input_name + "\ name=\"tusk_" + input_id + "\">";
            input_id++;
        }
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

function removeTagContent(tagName, content){
    var temp = document.getElementsByTagName(tagName);
    for(let i = 0; i < temp.length; i++){
        if(temp[i].innerHTML === content){
            temp[i].innerHTML = "";
        }
    }
}

var count = ~count~;
var num_quest = ~quest~;

function func() {
    var mas_main_div = document.querySelectorAll(".prob_maindiv");
    var ex = "";
    var temp_tusk;
    removeAllTag("a");
    removeAllTag("center");
    removeTagContent("p", "##");
    removeAllClass("outer_number");
    removeAllClass("briefcase");
    for(let i = 0; i < count;){
    temp_tusk = mas_main_div[getRandomInt(mas_main_div.length)];
        if(/\d/.test(temp_tusk.querySelector(".answer").querySelector("span").innerHTML)){
            temp_tusk.querySelector(".probtext").setAttribute("style", "display: block;");
            ex += temp_tusk.innerHTML;
            i++;
        }
    }
    document.head.innerHTML = "";
    document.body.innerHTML = "<link rel=\"stylesheet\" href=\"qrc:/MyStyle.css\">";
    document.body.innerHTML += ex;
    for(let j = 0; j < count; j++){
        document.getElementsByClassName("prob_nums")[j].textContent = "№ " + (num_quest + j + 1) + " - Тип 6";
    }
    setLineEdit();
    return document.body.innerHTML;
}func();
