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
    let arr_temp_maindiv = document.getElementsByClassName("prob_maindiv");
    let probtext;
    let pbody;
    for(let i = 0; i < arr_temp_maindiv.length; i++){
        probtext = arr_temp_maindiv[i].getElementsByClassName("probtext")[0];
        probtext.setAttribute("style", "display: block;");
        pbody = probtext.getElementsByClassName("pbody")[0];
        let input = document.createElement("input");
        input.type = "number";
        input.className = "number_field";
        pbody.appendChild(input);
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
        temp_nums[j].textContent = "№ " + (num_quest + j + 1) + " - Тип 5";
    }
}

function setTypeTask(){
    let temp_prob = document.getElementsByClassName("prob_maindiv");
    for(let i = 0; i < temp_prob.length; i++){
        let type_div = document.createElement("div");
        type_div.className = "prob_type";
        type_div.innerHTML = "numberimg";
        temp_prob[i].appendChild(type_div);
    }
}

function createSubForm(){
    let arr_main_div = document.querySelectorAll(".prob_maindiv");
    let temp_task;
    document.body.innerHTML = "<link rel=\"stylesheet\" href=\"qrc:/MyStyle.css\">";
    for(let i = 0; i < count;){
        temp_task = arr_main_div[getRandomInt(arr_main_div.length)];
        if(/\d/.test(temp_task.getElementsByClassName("prob_answer")[0].getElementsByTagName("div")[1].innerHTML)){
            document.body.appendChild(temp_task);
            i++;
        }
    }
}

var count = ~count~;
var num_quest = ~num_quest~;

function main() {
    removeAllTag("a");
    removeAllTag("center");
    removeAllClass("outer_number");
    removeAllClass("briefcase");
    removeAllClass("answer");
    createSubForm();
    correctionTaskNumber();
    setTypeTask();
    setLineEdit();
    return document.body.innerHTML;
}main();
