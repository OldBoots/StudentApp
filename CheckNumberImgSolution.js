function func() {
    let index_task = ~index_task~;
    let task = document.getElementsByClassName("prob_maindiv")[index_task];
    let field_text = task.getElementsByClassName("number_field")[0].value.replace(/[\n -]/gi, "").toLowerCase();
    let answer_text = task.getElementsByClassName("prob_answer")[0].getElementsByTagName("div")[1].innerHTML.replace(/[\n -]/gi, "").toLowerCase();
    if(answer_text.indexOf("|") !== -1){
        let list_variant_answer = answer_text.split("|");
        for(let i = 0; i < list_variant_answer.length; i++){
            if(list_variant_answer[i] === field_text){
        //        return "true";
                return answer_text + " + " + field_text;
            }
        }
    }else{
        if(answer_text === field_text){
    //        return "true";
            return answer_text + " + " + field_text;
        }
    }
    //        return "false";
            return answer_text + " - " + field_text;
} func();
