function get_type(index){
    let main_div = document.getElementsByClassName("maindiv")[index];
    let id_task = main_div.id.replace("id_", "");
    let type = document.getElementById("type_" + id_task).innerHTML;

    return type;
}

function check_string_num_task(index) {
    let main_div = document.getElementsByClassName("maindiv")[index];
    let id_task = main_div.id.replace("id_", "");
    let answer = document.getElementById("answer_" + id_task).innerHTML.replace(/[\n -]/gi, "").toLowerCase();
    let input_vlaue = document.getElementById("input_answer_" + id_task).value.replace(/[\n -]/gi, "").toLowerCase();
    if(answer.indexOf("|") !== -1){
        let list_variant_answer = answer.split("|");
        for(let i = 0; i < list_variant_answer.length; i++){
            if(list_variant_answer[i] === input_vlaue){
                                return 100;
//                return answer + " + " + input_vlaue;
            }
        }
    }else{
        if(answer === input_vlaue){
                        return 100;
//            return answer + " + " + input_vlaue;
        }
    }
        return 0;
//    return answer + " - " + input_vlaue;
}

function check_table_string_task(index) {
    let main_div = document.getElementsByClassName("maindiv")[index];
    let id_task = main_div.id.replace("id_", "");
    let answer = document.getElementById("answer_" + id_task).innerHTML.replace(/[\n -]/gi, "").toLowerCase();
    let input_vlaue = document.getElementById("textarea_" + id_task).value.replace(/[\n -]/gi, "").toLowerCase();

    if(answer.indexOf("|") !== -1){
        let list_variant_answer = answer.split("|");
        for(let i = 0; i < list_variant_answer.length; i++){
            if(list_variant_answer[i] === input_vlaue){
                                return 100;
//                return answer + " + " + input_vlaue;
            }
        }
    }else{
        if(answer === input_vlaue){
                        return 100;
//            return answer + " + " + input_vlaue;
        }
    }
        return 0;
//    return answer + " - " + input_vlaue;
}

function check_comp_task(index) {
    let main_div = document.getElementsByClassName("maindiv")[index];
    let id_task = main_div.id.replace("id_", "");
    let answer = document.getElementById("answer_" + id_task).innerHTML.replace(/[\n -]/gi, "").toLowerCase();
    let answer_list = answer.split("");
    let input_vlaue = main_div.getElementsByTagName("input");
    let count_true_ans = answer_list.length;
    let fraction = 0;
    for(let i = 0; i < input_vlaue.length; i++){
        if(input_vlaue[i].value.replace(/[\n -]/gi, "").toLowerCase() === answer_list[i]){
            fraction++;
        }
    }
        return Math.ceil((100.0 / count_true_ans) * fraction);
//    return answer + " - " + input_vlaue;
}

function check_multi_task(index) {
    let main_div = document.getElementsByClassName("maindiv")[index];
    let id_task = main_div.id.replace("id_", "");
    let checkbox_arr = main_div.getElementsByClassName("checkbox_field");
    let answer = document.getElementById("answer_" + id_task).innerHTML.replace(/[\n -]/gi, "").toLowerCase();
    let count_true_ans = answer.length;
    let fraction = 0;
    for(let i = 0; i < checkbox_arr.length; i++){
        if(answer.indexOf(i) !== -1){
            if(checkbox_arr[i].checked){
                fraction++;
            }
        }else{
            if(checkbox_arr[i].checked){
                fraction--;
            }
        }
    }
    if(fraction < 0){
        fraction = 0;
    }
    return Math.ceil((100.0 / count_true_ans) * fraction);
}

function check_28line_task(index){
    let count_true_ans = 2;
    let fraction = 0;
    let main_div = document.getElementsByClassName("maindiv")[index];
    let id_task = main_div.id.replace("id_", "");
    let answer_poly = document.getElementById("answer_" + id_task).innerHTML.replace(/[\n ]/gi, "").toLowerCase();
    let answer_iRNA = document.getElementById("answer_iRNA_" + id_task).innerHTML.replace(/[\n -]/gi, "").toLowerCase();
    let input_poly = document.getElementById("input_poly_" + id_task).value.replace(/[\n ]/gi, "").toLowerCase();
    let input_iRNA = document.getElementById("input_iRNA_" + id_task).value.replace(/[\n -]/gi, "").toLowerCase();
    if(answer_poly === input_poly){
        fraction++;
    }
    if(answer_iRNA === input_iRNA){
        fraction++;
    }
    return Math.ceil((100.0 / count_true_ans) * fraction);
}
