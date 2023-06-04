function getRandomInt(max){
    return Math.floor(Math.random() * max);
}

function removeAllClass(className){
    let temp = document.getElementsByClassName(className);
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
    let arr_temp_td = document.getElementsByTagName("td");
    for(let i = 0; i < arr_temp_td.length; i++){
        if(arr_temp_td[i].innerHTML === simbolHTML('&#8239;')){
            let input = document.createElement("input");
            input.type = "number";
            input.className = "table_number_field";
            arr_temp_td[i].innerHTML = "";
            arr_temp_td[i].appendChild(input);
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
        temp_nums[j].id = "nums_id" + (num_quest + j + 1);
        temp_nums[j].textContent = "№ " + (num_quest + j + 1) + " - Тип 6";
    }
}

function setTypeTask(){
    let temp_prob = document.getElementsByClassName("prob_maindiv");
    for(let i = 0; i < temp_prob.length; i++){
        let type_div = document.createElement("div");
        type_div.className = "prob_type";
        type_div.innerHTML = "numbertable";
        temp_prob[i].appendChild(type_div);
    }
}

function createSubForm(){
    let arr_main_div = document.querySelectorAll(".prob_maindiv");
    let arr_bool = new Array(arr_main_div.length).fill(true);
    let temp_num;
    let temp_task;
    document.body.innerHTML = "<link rel=\"stylesheet\" href=\"qrc:/MyStyle.css\">";
    for(let i = 0; i < count;){
        temp_num = getRandomInt(arr_main_div.length);
        if(arr_bool[temp_num]){
            arr_bool[temp_num] = false;
            temp_task = arr_main_div[temp_num];
            if(/\d/.test(temp_task.getElementsByClassName("prob_answer")[0].getElementsByTagName("div")[1].innerHTML)){
                document.body.appendChild(temp_task);
                i++;
            }
        }
    }
}

function removeSubStringInPTag(sub_string){
    let p = document.getElementsByTagName("p");
    for(let i = 0; i < p.length; i++){
        if(p[i].innerText.indexOf(sub_string) !== -1){
            p[i].innerText = p[i].innerText.replace(sub_string, ".");
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
    removeSubStringInPTag(": к каждой позиции, данной в первом столбце, подберите соответствующую позицию из второго столбца.");
    setTypeTask();
    setLineEdit();
    return document.body.innerHTML;
}main();
