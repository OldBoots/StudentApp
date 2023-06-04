function func() {
    let index_task = ~index_task~;
    let task = document.getElementsByClassName("prob_maindiv")[index_task];
    let field_text = task.getElementsByClassName("number_field")[0].value.replace(/[\n -]/gi, "");
    let answer_text = task.getElementsByClassName("prob_answer")[0].getElementsByTagName("div")[1].innerHTML.replace(/[\n -]/gi, "");
    if(answer_text === field_text){
                return 3;
//        return answer_text.toLowerCase() + " + " + field_text.toLowerCase();
    }
            return 0;
//    return answer_text.toLowerCase() + " - " + field_text.toLowerCase();
}func();
