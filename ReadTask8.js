function func() {
    var mas_main_div = document.getElementsByClassName("prob_maindiv");
    var ex = "";
    var count1 = 10;
    removeAllTag("a");
    removeAllClass("outer_number");
    removeAllClass("briefcase");

    for(let i = 0; i < count1; i++){
        ex += mas_main_div[getRandomInt(mas_main_div.length)].innerHTML;
    }
    document.head.innerHTML = "";
    document.body.innerHTML = "<link rel=\"stylesheet\" href=\"qrc:/MyStyle.css\">";
    document.body.innerHTML += ex;
    for(let j = 0; j < count1; j++){
        document.getElementsByClassName("prob_nums")[j].textContent = "№ " + (j + 1) + " - Тип 1";
    }
    setLineEdit();
}
