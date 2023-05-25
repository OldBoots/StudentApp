function func() {
    let index_task = ~index_task~;
    let field_text = "";
    let task = document.getElementsByClassName("prob_maindiv")[index_task];
    let arr_checkbox = task.getElementsByTagName("input");
    let answer_text = task.getElementsByClassName("prob_answer")[0].getElementsByTagName("div")[1].innerHTML.replace(/[\n -]/gi, "");
    let esti = 0;
    for(let i = 0, j = 0; i < arr_checkbox.length; i++){
        if(answer_text.indexOf(arr_checkbox[i].name) !== -1){
            if(arr_checkbox[i].checked){
                esti++;
            }
        }else{
            if(arr_checkbox[i].checked){
                esti--;
            }
        }
    }
    if(esti < 0){
        esti = 0;
    }
    return esti;
}func();
