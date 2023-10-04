#include "Graph.h"
#include "utils.h"

//function [path, length] = branch_n_bound (G)
void branch_n_bound(Graph G) {
	//    sz = size(G);
	int sz = G.vertexCount;

	//    A = G + diag(ones(1,sz(1)) + Inf);
	vector<vector<int>> A;

	// Заполняем A значениями из G с fakeINF по диагонали

	//    C = [ [0 1:sz(2) 0]' [1:sz(1); A; zeros(1,sz(2))] zeros(sz(1)+2, 1)];
	// Пока ситаем что добавляются лишние строки/столбцы с нумерацией.


	//    C = minH(C);
	//    C(1,1) = C(end, end);
	//    branch.C = C;
	//    branch.path = [];
	//    steps = [branch];
	//    do
	//        curBr = minBr(steps);
	//        C = steps(curBr).C;
	//        path = steps(curBr).path;
	//        steps = steps(1, [1:curBr-1, curBr+1:end]);
	//        C = minH(C);
	//        [h, coord] = maxO(C);
	//        C1 = C;
	//        arc = [C1(coord(1), 1), C1(1, coord(2))];
	//        C1 = setInf(C1, C1(1, coord(2)), C1(coord(1), 1));
	//        C1 = C1([1:coord(1)-1, coord(1)+1:end], 1:end);
	//        C1 = C1(1:end, [1:coord(2)-1, coord(2)+1:end]);
	//        C1 = minH(C1);
	//        C1(1, 1) = C1(1,1) + C1(end, end);
	//        branch1.C = C1;
	//        branch1.path = [path; arc];
	//        C2 = C;
	//        C2 = setInf(C2, C2(coord(1), 1), C2(1, coord(2)));
	//        C2(1,1) = C2(1,1) + h;
	//        branch2.C = C2;
	//        branch2.path = path;
	//        [curBr, vBr] = minBr(steps);
	//        steps = [steps, branch1];
	//        steps = [steps, branch2];
	//    until (size(path, 1) == sz(1)-1)
	//    arc = [C(2,1), C(1,2)];
	//    path = [path; arc];
	//    length = C(1,1);
	//endfunction
}

//function matr = minH (matr)
void minH(vector<vector<int>> matr) {
    //# в крайний правый столбец записываем минимумы по строкам
    //matr(2:end-1, end) = min(matr(2:end-1,2:end-1),[],2);
    //# вычитаем из элементов каждой строки минимум по этой строке
    //matr(2:end-1, 2:end-1) =  matr(2:end-1, 2:end-1) - matr(2:end-1, end);
    //# в крайний нижний строку записываем минимумы по столбцам
    //matr(end, 2:end-1) = min(matr(2:end-1,2:end-1),[],1);
    //# вычитаем из элементов каждой столбца минимум по этому столбцу
    //matr(2:end-1, 2:end-1) =  matr(2:end-1, 2:end-1) - matr(end, 2:end-1);

    //# сумма минимумов по строкам и слолбцам
    //matr(end, end) = sum(matr(2:end-1, end)) + sum(matr(end, 2:end-1));
}