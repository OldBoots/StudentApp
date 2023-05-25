function getRandomInt(max){
    return Math.floor(Math.random() * max);
}

function removeAllClass(className){
    let temp = document.getElementsByClassName(className);
    while(temp.length > 0){
        temp[0].parentNode.removeChild(temp[0]);
    }
}

function setLineEdit(){
    let arr_temp_div = document.getElementsByClassName("prob_maindiv");
    let arr_temp_td;
    let num_id;
    for(let i = 0; i < arr_temp_div.length; i++){
        arr_temp_td = arr_temp_div[i].getElementsByTagName("td");
        for(let j = 0; j < arr_temp_td.length; j++){
            if(arr_temp_td[j].innerHTML.length < 4){
                num_id = arr_temp_div[i].id.replace(/[a-z]/gi, '');
                arr_temp_td[j].innerHTML = "<textarea class=\"field\" style=\"width: calc(100%); height: calc(100%);\" id=\"string" + num_id + "\"</textarea>";
            }
        }
    }
}

function showSolution(){
    let temp = document.getElementsByClassName("solution");
    for(let i = 0; i < temp.length; i++){
        temp[i].setAttribute("style", "clear: both; display: block;");
    }
}

function removeAllTag(tagName){
    let temp = document.getElementsByTagName(tagName);
    while(temp.length > 0){
        temp[0].parentNode.removeChild(temp[0]);
    }
}

function correctionTaskNumber(){
    let temp_nums = document.getElementsByClassName("prob_nums");
    for(let j = 0; j < temp_nums.length; j++){
        temp_nums[j].textContent = "№ " + (num_quest + j + 1) + " - Тип 1";
    }
}

function setTypeTask(){
    let temp_prob = document.getElementsByClassName("prob_maindiv");
    for(let i = 0; i < temp_prob.length; i++){
        let type_div = document.createElement("div");
        type_div.className = "prob_type";
        type_div.innerHTML = "string";
        temp_prob[i].appendChild(type_div);
    }
}

function createSubForm(){
    let arr_main_div = document.querySelectorAll(".prob_maindiv");
    document.body.innerHTML = "<link rel=\"stylesheet\" href=\"qrc:/MyStyle.css\">";
    for(let i = 0; i < count; i++){
        document.body.appendChild(arr_main_div[getRandomInt(arr_main_div.length)]);
    }
}

var count = ~count~;
var num_quest = ~num_quest~;

function main() {
    removeAllTag("a");
    removeAllClass("outer_number");
    removeAllClass("briefcase");
    removeAllClass("answer");
    createSubForm();
    correctionTaskNumber();
    setTypeTask();
    setLineEdit();
    return document.body.innerHTML;
}main();
