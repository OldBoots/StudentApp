function get_fields(class_name) {
    let arr_fields = document.getElementsByClassName(class_name);
    let rezult_str = "";
    if(arr_fields.length > 0){
        for(let i = 0; i < arr_fields.length; i++){
            if(arr_fields[i].value.length === 0){
                rezult_str += "empty";
            }else{
                rezult_str += arr_fields[i].value;
            }
            if(i < arr_fields.length - 1){
                rezult_str += "~";
            }
        }
        return rezult_str;
    }
    return -1;
}

function get_checkbox() {
    let arr_fields = document.getElementsByClassName("checkbox_field");
    let rezult_str = "";
    if(arr_fields.length > 0){
        for(let i = 0; i < arr_fields.length; i++){
            if(arr_fields[i].checked){
                rezult_str += "true";
            }else{
                rezult_str += "false";
            }
            if(i < arr_fields.length - 1){
                rezult_str += "~";
            }
        }
        return rezult_str;
    }
    return -1;
}

function main() {
    let field_type = "~field_type~";
    let result_str;
    if(field_type === "string"){
        result_str = get_fields("field");
    }else if(field_type === "number"){
        result_str = get_fields("number_field");
    }else if(field_type === "table"){
        result_str = get_fields("table_number_field");
    }else if(field_type === "checkbox"){
        result_str = get_checkbox();
    } else {
        result_str = -1;
    }
    return result_str;
} main();
