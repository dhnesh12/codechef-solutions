#include <bits/stdc++.h>
#define eps 1e-10
#define pi std::acos(-1)
typedef long double ld;
ld sqr(ld x){
	return x * x;
}
struct point{
	ld x, y;
	point(){}
	point(ld _x, ld _y){
		x = _x; y = _y;
	}
	point operator + (const point &b) const{
		point ret = point(x, y);
		ret.x += b.x; ret.y += b.y; return ret;
	}
	point operator - (const point &b) const{
		point ret = point(x, y);
		ret.x -= b.x; ret.y -= b.y; return ret;
	}
	ld operator * (const point &b) const{
		return x * b.x + y * b.y;
	}
	ld len(){
		return std::sqrt(x * x + y * y);
	}
	ld len2(){
		return x * x + y * y;
	}
}p[1005];
ld dis(point a, point b){
	return std::sqrt(sqr(b.x - a.x) + sqr(b.y - a.y));
}
ld dis2(point a, point b){
	return sqr(b.x - a.x) + sqr(b.y - a.y);
}
struct line{
	point a1, a2;
	line(){}
	line(point _a1, point _a2){
		a1 = _a1; a2 = _a2;
	}
};

point cross(line l1, line l2){
	ld d1 = -l1.a2.y + l1.a1.y;
	ld e1 = -l1.a1.x + l1.a2.x;
	ld f1 = -l1.a1.x * l1.a2.y + l1.a1.y * l1.a2.x;
	ld d2 = -l2.a2.y + l2.a1.y;
	ld e2 = -l2.a1.x + l2.a2.x;
	ld f2 = -l2.a1.x * l2.a2.y + l2.a1.y * l2.a2.x;
	if(std::fabs(d1) < eps){
		std::swap(d1, d2); std::swap(e1, e2); std::swap(f1, f2);
	}
	e1 /= d1; f1 /= d1; d1 = 1;
	e2 -= d2 * e1; f2 -= d2 * f1; d2 = 0;
	f2 /= e2; e2 = 1; f1 -= f2 * e1; e1 = 0;
	return point(f1, f2);
}

struct circle{
	point C; ld r;
	circle(){}
	circle(point _C, ld _r){
		C = _C; r = _r;
	}
};

std::pair<point, point> cross(circle c1, circle c2){
	ld Y_x = -2 * (c2.C.x - c1.C.x) / 2 / (c2.C.y - c1.C.y);
	ld Y_c = (sqr(c1.r) - sqr(c2.r)) / 2 / (c2.C.y - c1.C.y);
	ld A = 1 + sqr(Y_x);
	ld B = -2 * c1.C.x + 2 * (Y_c - c1.C.y);
	ld C = sqr(c1.C.x) + sqr(Y_c - c1.C.y) - sqr(c1.r);
	ld delta = B * B - 4 * A * C;
	ld x1 = (-B + std::sqrt(delta)) / (2 * A);
	ld x2 = (-B - std::sqrt(delta)) / (2 * A);
	ld y1 = Y_x * x1 + Y_c;
	ld y2 = Y_x * x2 + Y_c;
	return std::make_pair(point(x1, y1), point(x2, y2));
}

int main(){
	std::cin >> p[0].x >> p[0].y;
	std::cin >> p[1].x >> p[1].y;
	std::cin >> p[2].x >> p[2].y;
	point p01 = p[1] - p[0];
	point p02 = p[2] - p[0];
	ld cx =  (p01 * p02) / (p01.len() * p02.len());
	cx = std::acos(cx) / pi * 180;
	std::cout.setf(std::ios::fixed);
	if(std::fabs(cx - 2) < 1e-8){
		printf("YES\n");
		std::cout << "Line " << std::fixed << std::setprecision(10) << p[0].x << " " << p[0].y << " " << p[1].x << " " << p[1].y << " " << std::endl;
		std::cout << "Line " << std::fixed << std::setprecision(10) << p[0].x << " " << p[0].y << " " << p[2].x << " " << p[2].y << " " << std::endl;
		std::cout << "Circle " << std::fixed << std::setprecision(10) << p[0].x << " " << p[0].y << " " << p[0].x << " " << p[0].y << " " << p[1].x << " " << p[1].y << " " << std::endl;
		ld dx = p01.len() / p02.len();
		p02.x *= dx; p02.y *= dx;
		p[2] = p[0] + p02;
		std::cout << "Circle " << std::fixed << std::setprecision(10) << p[1].x << " " << p[1].y << " " << p[1].x << " " << p[1].y << " " << p[2].x << " " << p[2].y << " " << std::endl;
		std::cout << "Circle " << std::fixed << std::setprecision(10) << p[2].x << " " << p[2].y << " " << p[1].x << " " << p[1].y << " " << p[2].x << " " << p[2].y << " " << std::endl;
		p[3].x = (p[1].x + p[2].x) / 2;
		p[3].y = (p[1].y + p[2].y) / 2;
		point pd2 = p[2] - p[1];
		std::swap(pd2.x, pd2.y);
		pd2.x *= (-std::sqrt(3) / 2); pd2.y *= (std::sqrt(3) / 2);
		p[3] = p[3] + pd2;
		std::cout << "Line " << std::fixed << std::setprecision(10) << p[0].x << " " << p[0].y << " " << p[3].x << " " << p[3].y << " " << std::endl;
		std::cout << "Answer" << std::endl;
		std::cout << p[3].x << " " << p[3].y << std::endl;
		
	}
	if(std::fabs(cx - 4) < 1e-8){printf("YES\n");
		std::cout << "Line " << std::fixed << std::setprecision(10) << p[0].x << " " << p[0].y << " " << p[1].x << " " << p[1].y << " " << std::endl;
		std::cout << "Line " << std::fixed << std::setprecision(10) << p[0].x << " " << p[0].y << " " << p[2].x << " " << p[2].y << " " << std::endl;
		std::cout << "Circle " << std::fixed << std::setprecision(10) << p[0].x << " " << p[0].y << " " << p[0].x << " " << p[0].y << " " << p[1].x << " " << p[1].y << " " << std::endl;
		ld dx = p01.len() / p02.len();
		p02.x *= dx; p02.y *= dx;
		p[2] = p[0] + p02;
		std::cout << "Circle " << std::fixed << std::setprecision(10) << p[1].x << " " << p[1].y << " " << p[1].x << " " << p[1].y << " " << p[2].x << " " << p[2].y << " " << std::endl;
		std::cout << "Circle " << std::fixed << std::setprecision(10) << p[2].x << " " << p[2].y << " " << p[1].x << " " << p[1].y << " " << p[2].x << " " << p[2].y << " " << std::endl;
		p[3].x = (p[1].x + p[2].x) / 2;
		p[3].y = (p[1].y + p[2].y) / 2;
		point pd2 = p[2] - p[1];
		std::swap(pd2.x, pd2.y);
		pd2.x *= (-std::sqrt(3) / 2); pd2.y *= (std::sqrt(3) / 2);
		p[3] = p[3] + pd2;
		std::cout << "Line " << std::fixed << std::setprecision(10) << p[0].x << " " << p[0].y << " " << p[3].x << " " << p[3].y << " " << std::endl;
		
		std::cout << "Circle " << std::fixed << std::setprecision(10) << p[0].x << " " << p[0].y << " " << p[0].x << " " << p[0].y << " " << p[1].x << " " << p[1].y << " " << std::endl;
		point p03 = p[3] - p[0];
		ld dx2 = p01.len() / p03.len();
		p03.x *= dx2; p03.y *= dx2;
		p[3] = p[0] + p03;
		std::cout << "Circle " << std::fixed << std::setprecision(10) << p[1].x << " " << p[1].y << " " << p[1].x << " " << p[1].y << " " << p[3].x << " " << p[3].y << " " << std::endl;
		std::cout << "Circle " << std::fixed << std::setprecision(10) << p[3].x << " " << p[3].y << " " << p[1].x << " " << p[1].y << " " << p[3].x << " " << p[3].y << " " << std::endl;
		p[4].x = (p[1].x + p[3].x) / 2;
		p[4].y = (p[1].y + p[3].y) / 2;
		point pd3 = p[3] - p[1];
		std::swap(pd3.x, pd3.y);
		pd3.x *= (-std::sqrt(3) / 2); pd3.y *= (std::sqrt(3) / 2);
		p[4] = p[4] + pd3;
		std::cout << "Line " << std::fixed << std::setprecision(10) << p[0].x << " " << p[0].y << " " << p[4].x << " " << p[4].y << " " << std::endl;
	
		std::cout << "Circle " << std::fixed << std::setprecision(10) << p[0].x << " " << p[0].y << " " << p[0].x << " " << p[0].y << " " << p[3].x << " " << p[3].y << " " << std::endl;
		std::cout << "Circle " << std::fixed << std::setprecision(10) << p[3].x << " " << p[3].y << " " << p[3].x << " " << p[3].y << " " << p[2].x << " " << p[2].y << " " << std::endl;
		std::cout << "Circle " << std::fixed << std::setprecision(10) << p[2].x << " " << p[2].y << " " << p[3].x << " " << p[3].y << " " << p[2].x << " " << p[2].y << " " << std::endl;
		p[5].x = (p[3].x + p[2].x) / 2;
		p[5].y = (p[3].y + p[2].y) / 2;
		point pd4 = p[2] - p[3];
		std::swap(pd4.x, pd4.y);
		pd4.x *= (-std::sqrt(3) / 2); pd4.y *= (std::sqrt(3) / 2);
		p[5] = p[5] + pd4;
		std::cout << "Line " << std::fixed << std::setprecision(10) << p[0].x << " " << p[0].y << " " << p[5].x << " " << p[5].y << " " << std::endl;
		std::cout << "Answer" << std::endl;
		std::cout << p[4].x << " " << p[4].y << std::endl;
		std::cout << p[3].x << " " << p[3].y << std::endl;
		std::cout << p[5].x << " " << p[5].y << std::endl;
	}
	if(std::fabs(cx - 3) < 1e-8){printf("NO\n");
	}
	if(std::fabs(cx - 1) < 1e-8){printf("YES\nAnswer\n");
	}
	if(cx > 4){
		int fafa = (int)(cx + 0.1);
	while(fafa % 2 == 0) fafa /= 2;

		printf("NO\n");
	
	}
	return 0;
}