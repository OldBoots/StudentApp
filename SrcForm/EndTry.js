function disable_form() {
    let arr_input = document.getElementsByTagName("input");
    for(let i = 0; i < arr_input.length; i++){
        arr_input[i].disabled = true;
    }
    let arr_texterea = document.getElementsByTagName("textarea");
    for(let j = 0; j < arr_input.length; j++){
        arr_texterea[j].disabled = true;
    }
}

function show_solution() {
    let temp = document.getElementsByClassName("solution");
    for(let i = 0; i < temp.length; i++){
        temp[i].setAttribute("style", "clear: both; display: block;");
    }
}
