function func() {
    let arr_number_fields = document.getElementsByClassName("checkbox_field");
    let rezult_str = "";
    if(arr_number_fields.length > 0){
        for(let i = 0; i < arr_number_fields.length; i++){
            if(arr_number_fields[i].checked){
                rezult_str += "true";
            }else{
                rezult_str += "false";
            }
            if(i < arr_number_fields.length - 1){
                rezult_str += "\n";
            }
        }
        return rezult_str;
    }
    return -1;
} func();
