function func() {
    let index_task = ~index_task~;
    let task = document.getElementsByClassName("prob_maindiv")[index_task];
    let arr_field = task.getElementsByClassName("table_number_field");
    let answer_text = task.getElementsByClassName("prob_answer")[0].getElementsByTagName("div")[1].innerHTML.replace(/[\n -]/gi, "");
    let field_text = "";
    for(let i = 0; i < arr_field.length; i++){
        field_text += arr_field[i].value;
    }
    if(answer_text === field_text){
                return 3;
//        return answer_text + " + " + field_text;
    }
            return 0;
//    return answer_text + " - " + field_text;
}func();
