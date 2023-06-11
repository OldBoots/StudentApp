function load_checkbox_prog(str_value){
    let field_arr = document.getElementsByName("checkbox");
    let list_value = str_value.split("~");
    for(let i = 0; i < list_value.length; i++){
        if(list_value[i] !== ""){
            if(list_value[i] === "true"){
                field_arr[i].checked = true;
            }else{
                field_arr[i].checked = false;
            }
        }
    }
}

function load_textarea_prog(str_value){
    let field_arr = document.getElementsByName("textarea");
    if(str_value.indexOf("~") < 0){
        if(str_value !== "empty"){
            field_arr.value = str_value;
        }
    }else{
        let list_value = str_value.split("~");
        for(let i = 0; i < list_value.length; i++){
            if(list_value[i] !== "" && str_value !== "empty"){
                field_arr[i].value = list_value[i];
            }
        }
    }
}

function load_input_prog(str_value){
    let field_arr = document.getElementsByName("input");
    if(str_value.indexOf("~") < 0){
        if(str_value !== "empty"){
            field_arr.value = str_value;
        }
    }else{
        let list_value = str_value.split("~");
        for(let i = 0; i < list_value.length; i++){
            if(list_value[i] !== "" && str_value !== "empty"){
                field_arr[i].value = list_value[i];
            }
        }
    }
}
