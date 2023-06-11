function save_progress() {
    let input_arr = document.getElementsByName("input");
    let textarea_arr = document.getElementsByName("textarea");
    let checkbox_arr = document.getElementsByName("checkbox");
    let result_str = "";
    for(let i = 0; i < input_arr.length; i++){
        if(input_arr[i].value.length === 0){
            result_str += "i=empty";
        }else{
            result_str += "i=" + input_arr[i].value;
        }
        result_str += "~";
    }
    for(let j = 0; j < textarea_arr.length; j++){
        if(textarea_arr[j].value.length === 0){
            result_str += "t=empty";
        }else{
            textarea_arr += "t=" + textarea_arr[j].value;
        }
        result_str += "~";
    }
    for(let g = 0; g < checkbox_arr.length; g++){
        if(checkbox_arr[g].checked){
            result_str += "c=true";
        }else{
            result_str += "c=false";
        }
        result_str += "~";
    }
    return result_str;
}
