function step(num) 
{
    var rez = num * num;
    return Math.floor(rez);
}

function koren(num)
{
if (num >= 0){
var result=Math.sqrt(num);
}
else
{
document.write("<br>");
document.write("������� ���������� ����������� ����� �� �������������� �����, ���������� �� ������!!!");
var result=Math.sqrt(Math.abs(num));
}
return Math.floor(result);
}


