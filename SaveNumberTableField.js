function func() {
    let arr_number_fields = document.getElementsByClassName("table_number_field");
    let rezult_str = "";
    if(arr_number_fields.length > 0){
        for(let i = 0; i < arr_number_fields.length; i++){
            rezult_str += arr_number_fields[i].value;
            if(i < arr_number_fields.length - 1){
                rezult_str += "\n";
            }
        }
        return rezult_str;
    }
    return -1;
} func();
