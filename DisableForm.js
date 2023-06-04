function func() {
    let arr_input = document.getElementsByTagName("input");
    for(let i = 0; i < arr_input.length; i++){
//        arr_input[i].readOnly = true;
        arr_input[i].disabled = true;
    }
} func();
