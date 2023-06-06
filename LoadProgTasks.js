function set_value(class_name, str){
    let arr_number_fields = document.getElementsByClassName(class_name);
    if(str.indexOf("~") > 0){
        let list_value = str.split("~");
        for(let i = 0; i < list_value.length; i++){
            arr_number_fields[i].value = list_value[i];
        }
    }else{
        arr_number_fields[0].value = str;
    }
}

function set_state(str){
let arr_number_fields = document.getElementsByClassName("checkbox_field");
    let list_value = str.split("~");
    for(let i = 0; i < list_value.length; i++){
        if(list_value[i] === "true"){
            arr_number_fields[i].checked = true;
        }else{
            arr_number_fields[i].checked = false;
        }
    }
}

function main() {
    let field_type = "~field_type~";
    let str = "~str~";
    if(field_type === "string"){
        set_value("field", str);
    }else if(field_type === "number"){
        set_value("number_field", str);
    }else if(field_type === "table"){
        set_value("table_number_field", str);
    }else if(field_type === "checkbox"){
        set_state(str);
    }else {
        return -1;
    }
    return str;
} main();
