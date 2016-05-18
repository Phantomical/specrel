#include "Torus.h"
#include "MathUtils.h"
#include "Sphere.h"

namespace 
{
	template<uintmax_t N>
	constexpr typename std::enable_if<N == 2, double>::type pow(double v)
	{
		return v * v;
	}
	template<uintmax_t N>
	constexpr typename std::enable_if<N == 1, double>::type pow(double v)
	{
		return v;
	}
	template<uintmax_t N>
	constexpr typename std::enable_if<N == 0, double>::type pow(double v)
	{
		return 1.0;
	}
	template<uintmax_t N>
	constexpr typename std::enable_if<(N & 1) == 0 && (N > 2), double>::type pow(double v)
	{
		return pow<2>(pow<N / 2>(v));
	}
	template<uintmax_t N>
	constexpr typename std::enable_if<(N & 1) == 1 && (N > 2), double>::type pow(double v)
	{
		return pow<N - 1>(v) * v;
	}

	constexpr double val = pow<SIZE_MAX>(0.9999999999999999);
}

#define V RefFrame.Velocity
#define S InitialPosition
#define O ray.Origin
#define D ray.Direction

#define Vx V.x
#define Vy V.y
#define Vz V.z

#define Dx D.x
#define Dy D.y
#define Dz D.z

#define Sx S.x
#define Sy S.y
#define Sz S.z
#define St S.t

#define Ox O.x
#define Oy O.y
#define Oz O.z
#define Ot O.t

#define Power(v, n) pow<n>(v)

#define r RingRadius
#define R Radius

IntersectionList Torus::AllIntersections(const Ray& _ray) const
{
	Ray ray = LorentzTransform(_ray, RefFrame);

	{
		//Use sphere for an early exit
		Sphere sphere{ InitialPosition, Radius + RingRadius, Colour, RefFrame };
		if (!sphere.AnyIntersections(ray))
			//No intersections (The ray didn't hit the sphere)
			return IntersectionList();
	}

	std::vector<double> slns;

	{
#if 1
		const double tmp563 = Power(Ot, 4);
		const double tmp562 = Power(St, 4);
		const double tmp169 = Power(Oy, 2);
		const double tmp154 = Power(Sx, 2);
		const double tmp167 = Power(Oz, 2);
		const double tmp165 = Power(r, 2);
		const double tmp163 = Power(R, 2);
		const double tmp150 = Power(Sy, 2);
		const double tmp146 = Power(Sz, 2);
		const double tmp542 = Power(Ox, 3);
		const double tmp171 = Power(Ox, 2);
		const double tmp525 = Power(Sx, 3);
		const double tmp8 = Power(Vx, 2);
		const double tmp132 = Power(St, 2);
		const double tmp27 = Power(Vx, 3);
		const double tmp350 = Power(St, 3);
		const double tmp26 = Power(Vx, 4);
		const double tmp490 = Power(Oy, 3);
		const double tmp468 = Power(Sy, 3);
		const double tmp5 = Power(Vy, 2);
		const double tmp20 = Power(Vy, 3);
		const double tmp19 = Power(Vy, 4);
		const double tmp425 = Power(Oz, 3);
		const double tmp4 = Power(Vz, 2);
		const double tmp2 = Power(Vz, 3);
		const double tmp351 = Power(Ot, 3);
		const double tmp1 = Power(Vz, 4);
		const double tmp133 = Power(Ot, 2);
		const double tmp12 = Power(Dx, 2);
		const double tmp11 = Power(Dy, 2);
		const double tmp10 = Power(Dz, 2);
		const double tmp28 = Power(Dx, 3);
		const double tmp25 = Power(Dy, 3);
		const double tmp17 = Power(Dz, 3);
		const double tmp398 = Power(Sz, 3);
		const double tmp560 = (tmp169*Sx);
		const double tmp559 = (tmp167*Sx);
		const double tmp558 = (tmp165*Sx);
		const double tmp557 = (tmp163*Sx);
		const double tmp556 = (tmp167*Sy);
		const double tmp555 = (tmp165*Sy);
		const double tmp554 = (tmp163*Sy);
		const double tmp342 = (Sx*Sy);
		const double tmp553 = (Oy*tmp342);
		const double tmp552 = (tmp154*Sy);
		const double tmp551 = (Sx*tmp150);
		const double tmp550 = (tmp165*Sz);
		const double tmp549 = (tmp163*Sz);
		const double tmp340 = (Sx*Sz);
		const double tmp548 = (Oz*tmp340);
		const double tmp547 = (tmp154*Sz);
		const double tmp339 = (Sy*Sz);
		const double tmp546 = (Oz*tmp339);
		const double tmp545 = (tmp150*Sz);
		const double tmp544 = (Sx*tmp146);
		const double tmp543 = (Sy*tmp146);
		const double tmp541 = (tmp542*Vx);
		const double tmp335 = (tmp169*Vx);
		const double tmp540 = (Ox*tmp335);
		const double tmp333 = (tmp167*Vx);
		const double tmp539 = (Ox*tmp333);
		const double tmp332 = (tmp165*Vx);
		const double tmp538 = (Ox*tmp332);
		const double tmp331 = (tmp163*Vx);
		const double tmp537 = (Ox*tmp331);
		const double tmp123 = (St*Vx);
		const double tmp536 = (tmp169*tmp123);
		const double tmp535 = (tmp167*tmp123);
		const double tmp534 = (tmp165*tmp123);
		const double tmp533 = (tmp163*tmp123);
		const double tmp122 = (Sx*Vx);
		const double tmp532 = (tmp171*tmp122);
		const double tmp531 = (tmp169*tmp122);
		const double tmp530 = (tmp167*tmp122);
		const double tmp529 = (tmp165*tmp122);
		const double tmp528 = (tmp163*tmp122);
		const double tmp322 = (tmp154*Vx);
		const double tmp527 = (Ox*tmp322);
		const double tmp526 = (St*tmp322);
		const double tmp524 = (tmp525*Vx);
		const double tmp121 = (Sy*Vx);
		const double tmp320 = (Oy*tmp121);
		const double tmp523 = (Ox*tmp320);
		const double tmp319 = (St*tmp121);
		const double tmp522 = (Oy*tmp319);
		const double tmp318 = (Sx*tmp121);
		const double tmp521 = (Oy*tmp318);
		const double tmp520 = (St*tmp318);
		const double tmp317 = (tmp150*Vx);
		const double tmp519 = (Ox*tmp317);
		const double tmp518 = (St*tmp317);
		const double tmp517 = (Sx*tmp317);
		const double tmp120 = (Sz*Vx);
		const double tmp315 = (Oz*tmp120);
		const double tmp516 = (Ox*tmp315);
		const double tmp314 = (St*tmp120);
		const double tmp515 = (Oz*tmp314);
		const double tmp313 = (Sx*tmp120);
		const double tmp514 = (Oz*tmp313);
		const double tmp513 = (St*tmp313);
		const double tmp312 = (tmp146*Vx);
		const double tmp512 = (Ox*tmp312);
		const double tmp511 = (St*tmp312);
		const double tmp510 = (Sx*tmp312);
		const double tmp115 = (St*tmp8);
		const double tmp509 = (tmp171*tmp115);
		const double tmp508 = (tmp169*tmp115);
		const double tmp507 = (tmp167*tmp115);
		const double tmp506 = (tmp165*tmp115);
		const double tmp505 = (tmp163*tmp115);
		const double tmp114 = (Sx*tmp8);
		const double tmp299 = (St*tmp114);
		const double tmp504 = (Ox*tmp299);
		const double tmp503 = (tmp132*tmp114);
		const double tmp298 = (tmp154*tmp8);
		const double tmp502 = (St*tmp298);
		const double tmp113 = (Sy*tmp8);
		const double tmp296 = (St*tmp113);
		const double tmp501 = (Oy*tmp296);
		const double tmp500 = (tmp132*tmp113);
		const double tmp295 = (tmp150*tmp8);
		const double tmp499 = (St*tmp295);
		const double tmp112 = (Sz*tmp8);
		const double tmp293 = (St*tmp112);
		const double tmp498 = (Oz*tmp293);
		const double tmp497 = (tmp132*tmp112);
		const double tmp292 = (tmp146*tmp8);
		const double tmp496 = (St*tmp292);
		const double tmp290 = (tmp132*tmp27);
		const double tmp495 = (Ox*tmp290);
		const double tmp494 = (tmp350*tmp27);
		const double tmp109 = (Sx*tmp27);
		const double tmp493 = (tmp132*tmp109);
		const double tmp492 = (tmp350*tmp26);
		const double tmp105 = (Oy*Vy);
		const double tmp491 = (tmp171*tmp105);
		const double tmp489 = (tmp490*Vy);
		const double tmp282 = (tmp167*Vy);
		const double tmp488 = (Oy*tmp282);
		const double tmp281 = (tmp165*Vy);
		const double tmp487 = (Oy*tmp281);
		const double tmp280 = (tmp163*Vy);
		const double tmp486 = (Oy*tmp280);
		const double tmp103 = (St*Vy);
		const double tmp485 = (tmp167*tmp103);
		const double tmp484 = (tmp165*tmp103);
		const double tmp483 = (tmp163*tmp103);
		const double tmp102 = (Sx*Vy);
		const double tmp276 = (Oy*tmp102);
		const double tmp482 = (Ox*tmp276);
		const double tmp275 = (St*tmp102);
		const double tmp481 = (Oy*tmp275);
		const double tmp274 = (tmp154*Vy);
		const double tmp480 = (Oy*tmp274);
		const double tmp479 = (St*tmp274);
		const double tmp101 = (Sy*Vy);
		const double tmp478 = (tmp171*tmp101);
		const double tmp477 = (tmp169*tmp101);
		const double tmp476 = (tmp167*tmp101);
		const double tmp475 = (tmp165*tmp101);
		const double tmp474 = (tmp163*tmp101);
		const double tmp268 = (Sx*tmp101);
		const double tmp473 = (Ox*tmp268);
		const double tmp472 = (St*tmp268);
		const double tmp471 = (tmp154*tmp101);
		const double tmp267 = (tmp150*Vy);
		const double tmp470 = (Oy*tmp267);
		const double tmp469 = (St*tmp267);
		const double tmp467 = (tmp468*Vy);
		const double tmp100 = (Sz*Vy);
		const double tmp265 = (Oz*tmp100);
		const double tmp466 = (Oy*tmp265);
		const double tmp264 = (St*tmp100);
		const double tmp465 = (Oz*tmp264);
		const double tmp263 = (Sy*tmp100);
		const double tmp464 = (Oz*tmp263);
		const double tmp463 = (St*tmp263);
		const double tmp262 = (tmp146*Vy);
		const double tmp462 = (Oy*tmp262);
		const double tmp461 = (St*tmp262);
		const double tmp460 = (Sy*tmp262);
		const double tmp24 = (Vx*Vy);
		const double tmp97 = (St*tmp24);
		const double tmp259 = (Oy*tmp97);
		const double tmp459 = (Ox*tmp259);
		const double tmp258 = (tmp132*tmp24);
		const double tmp458 = (Oy*tmp258);
		const double tmp96 = (Sx*tmp24);
		const double tmp256 = (St*tmp96);
		const double tmp457 = (Oy*tmp256);
		const double tmp456 = (tmp132*tmp96);
		const double tmp95 = (Sy*tmp24);
		const double tmp254 = (St*tmp95);
		const double tmp455 = (Ox*tmp254);
		const double tmp454 = (tmp132*tmp95);
		const double tmp253 = (Sx*tmp95);
		const double tmp453 = (St*tmp253);
		const double tmp23 = (tmp8*Vy);
		const double tmp251 = (tmp132*tmp23);
		const double tmp452 = (Oy*tmp251);
		const double tmp451 = (tmp350*tmp23);
		const double tmp92 = (Sy*tmp23);
		const double tmp450 = (tmp132*tmp92);
		const double tmp87 = (St*tmp5);
		const double tmp449 = (tmp171*tmp87);
		const double tmp448 = (tmp169*tmp87);
		const double tmp447 = (tmp167*tmp87);
		const double tmp446 = (tmp165*tmp87);
		const double tmp445 = (tmp163*tmp87);
		const double tmp86 = (Sx*tmp5);
		const double tmp237 = (St*tmp86);
		const double tmp444 = (Ox*tmp237);
		const double tmp443 = (tmp132*tmp86);
		const double tmp236 = (tmp154*tmp5);
		const double tmp442 = (St*tmp236);
		const double tmp85 = (Sy*tmp5);
		const double tmp234 = (St*tmp85);
		const double tmp441 = (Oy*tmp234);
		const double tmp440 = (tmp132*tmp85);
		const double tmp233 = (tmp150*tmp5);
		const double tmp439 = (St*tmp233);
		const double tmp84 = (Sz*tmp5);
		const double tmp231 = (St*tmp84);
		const double tmp438 = (Oz*tmp231);
		const double tmp437 = (tmp132*tmp84);
		const double tmp230 = (tmp146*tmp5);
		const double tmp436 = (St*tmp230);
		const double tmp22 = (Vx*tmp5);
		const double tmp228 = (tmp132*tmp22);
		const double tmp435 = (Ox*tmp228);
		const double tmp434 = (tmp350*tmp22);
		const double tmp81 = (Sx*tmp22);
		const double tmp433 = (tmp132*tmp81);
		const double tmp21 = (tmp8*tmp5);
		const double tmp432 = (tmp350*tmp21);
		const double tmp224 = (tmp132*tmp20);
		const double tmp431 = (Oy*tmp224);
		const double tmp430 = (tmp350*tmp20);
		const double tmp77 = (Sy*tmp20);
		const double tmp429 = (tmp132*tmp77);
		const double tmp428 = (tmp350*tmp19);
		const double tmp71 = (Oz*Vz);
		const double tmp427 = (tmp171*tmp71);
		const double tmp426 = (tmp169*tmp71);
		const double tmp424 = (tmp425*Vz);
		const double tmp215 = (tmp165*Vz);
		const double tmp423 = (Oz*tmp215);
		const double tmp214 = (tmp163*Vz);
		const double tmp422 = (Oz*tmp214);
		const double tmp69 = (St*Vz);
		const double tmp421 = (tmp165*tmp69);
		const double tmp420 = (tmp163*tmp69);
		const double tmp68 = (Sx*Vz);
		const double tmp211 = (Oz*tmp68);
		const double tmp419 = (Ox*tmp211);
		const double tmp210 = (St*tmp68);
		const double tmp418 = (Oz*tmp210);
		const double tmp209 = (tmp154*Vz);
		const double tmp417 = (Oz*tmp209);
		const double tmp416 = (St*tmp209);
		const double tmp67 = (Sy*Vz);
		const double tmp207 = (Oz*tmp67);
		const double tmp415 = (Oy*tmp207);
		const double tmp206 = (St*tmp67);
		const double tmp414 = (Oz*tmp206);
		const double tmp205 = (tmp150*Vz);
		const double tmp413 = (Oz*tmp205);
		const double tmp412 = (St*tmp205);
		const double tmp66 = (Sz*Vz);
		const double tmp411 = (tmp171*tmp66);
		const double tmp410 = (tmp169*tmp66);
		const double tmp409 = (tmp167*tmp66);
		const double tmp408 = (tmp165*tmp66);
		const double tmp407 = (tmp163*tmp66);
		const double tmp199 = (Sx*tmp66);
		const double tmp406 = (Ox*tmp199);
		const double tmp405 = (St*tmp199);
		const double tmp404 = (tmp154*tmp66);
		const double tmp198 = (Sy*tmp66);
		const double tmp403 = (Oy*tmp198);
		const double tmp402 = (St*tmp198);
		const double tmp401 = (tmp150*tmp66);
		const double tmp197 = (tmp146*Vz);
		const double tmp400 = (Oz*tmp197);
		const double tmp399 = (St*tmp197);
		const double tmp397 = (tmp398*Vz);
		const double tmp16 = (Vx*Vz);
		const double tmp63 = (St*tmp16);
		const double tmp194 = (Oz*tmp63);
		const double tmp396 = (Ox*tmp194);
		const double tmp193 = (tmp132*tmp16);
		const double tmp395 = (Oz*tmp193);
		const double tmp62 = (Sx*tmp16);
		const double tmp191 = (St*tmp62);
		const double tmp394 = (Oz*tmp191);
		const double tmp393 = (tmp132*tmp62);
		const double tmp61 = (Sz*tmp16);
		const double tmp189 = (St*tmp61);
		const double tmp392 = (Ox*tmp189);
		const double tmp391 = (tmp132*tmp61);
		const double tmp188 = (Sx*tmp61);
		const double tmp390 = (St*tmp188);
		const double tmp15 = (tmp8*Vz);
		const double tmp186 = (tmp132*tmp15);
		const double tmp389 = (Oz*tmp186);
		const double tmp388 = (tmp350*tmp15);
		const double tmp58 = (Sz*tmp15);
		const double tmp387 = (tmp132*tmp58);
		const double tmp14 = (Vy*Vz);
		const double tmp55 = (St*tmp14);
		const double tmp182 = (Oz*tmp55);
		const double tmp386 = (Oy*tmp182);
		const double tmp181 = (tmp132*tmp14);
		const double tmp385 = (Oz*tmp181);
		const double tmp54 = (Sy*tmp14);
		const double tmp179 = (St*tmp54);
		const double tmp384 = (Oz*tmp179);
		const double tmp383 = (tmp132*tmp54);
		const double tmp53 = (Sz*tmp14);
		const double tmp177 = (St*tmp53);
		const double tmp382 = (Oy*tmp177);
		const double tmp381 = (tmp132*tmp53);
		const double tmp176 = (Sy*tmp53);
		const double tmp380 = (St*tmp176);
		const double tmp13 = (tmp5*Vz);
		const double tmp174 = (tmp132*tmp13);
		const double tmp379 = (Oz*tmp174);
		const double tmp378 = (tmp350*tmp13);
		const double tmp50 = (Sz*tmp13);
		const double tmp377 = (tmp132*tmp50);
		const double tmp45 = (St*tmp4);
		const double tmp376 = (tmp171*tmp45);
		const double tmp375 = (tmp169*tmp45);
		const double tmp374 = (tmp167*tmp45);
		const double tmp373 = (tmp165*tmp45);
		const double tmp372 = (tmp163*tmp45);
		const double tmp44 = (Sx*tmp4);
		const double tmp155 = (St*tmp44);
		const double tmp371 = (Ox*tmp155);
		const double tmp370 = (tmp132*tmp44);
		const double tmp153 = (tmp154*tmp4);
		const double tmp369 = (St*tmp153);
		const double tmp43 = (Sy*tmp4);
		const double tmp151 = (St*tmp43);
		const double tmp368 = (Oy*tmp151);
		const double tmp367 = (tmp132*tmp43);
		const double tmp149 = (tmp150*tmp4);
		const double tmp366 = (St*tmp149);
		const double tmp42 = (Sz*tmp4);
		const double tmp147 = (St*tmp42);
		const double tmp365 = (Oz*tmp147);
		const double tmp364 = (tmp132*tmp42);
		const double tmp145 = (tmp146*tmp4);
		const double tmp363 = (St*tmp145);
		const double tmp9 = (Vx*tmp4);
		const double tmp143 = (tmp132*tmp9);
		const double tmp362 = (Ox*tmp143);
		const double tmp361 = (tmp350*tmp9);
		const double tmp39 = (Sx*tmp9);
		const double tmp360 = (tmp132*tmp39);
		const double tmp7 = (tmp8*tmp4);
		const double tmp359 = (tmp350*tmp7);
		const double tmp6 = (Vy*tmp4);
		const double tmp139 = (tmp132*tmp6);
		const double tmp358 = (Oy*tmp139);
		const double tmp357 = (tmp350*tmp6);
		const double tmp35 = (Sy*tmp6);
		const double tmp356 = (tmp132*tmp35);
		const double tmp3 = (tmp5*tmp4);
		const double tmp355 = (tmp350*tmp3);
		const double tmp135 = (tmp132*tmp2);
		const double tmp354 = (Oz*tmp135);
		const double tmp353 = (tmp350*tmp2);
		const double tmp31 = (Sz*tmp2);
		const double tmp352 = (tmp132*tmp31);
		const double tmp349 = (tmp350*tmp1);
		const double tmp344 = (Oy*Sy);
		const double tmp341 = (Oz*Sz);
		const double tmp323 = (St*tmp122);
		const double tmp310 = (tmp171*tmp8);
		const double tmp309 = (tmp169*tmp8);
		const double tmp308 = (tmp167*tmp8);
		const double tmp307 = (tmp165*tmp8);
		const double tmp306 = (tmp163*tmp8);
		const double tmp301 = (tmp132*tmp8);
		const double tmp300 = (Ox*tmp114);
		const double tmp297 = (Oy*tmp113);
		const double tmp294 = (Oz*tmp112);
		const double tmp110 = (St*tmp27);
		const double tmp291 = (Ox*tmp110);
		const double tmp289 = (St*tmp109);
		const double tmp288 = (tmp132*tmp26);
		const double tmp279 = (Oy*tmp103);
		const double tmp269 = (St*tmp101);
		const double tmp98 = (Oy*tmp24);
		const double tmp261 = (Ox*tmp98);
		const double tmp257 = (Oy*tmp96);
		const double tmp255 = (Ox*tmp95);
		const double tmp93 = (St*tmp23);
		const double tmp252 = (Oy*tmp93);
		const double tmp250 = (St*tmp92);
		const double tmp248 = (tmp171*tmp5);
		const double tmp247 = (tmp169*tmp5);
		const double tmp246 = (tmp167*tmp5);
		const double tmp245 = (tmp165*tmp5);
		const double tmp244 = (tmp163*tmp5);
		const double tmp239 = (tmp132*tmp5);
		const double tmp238 = (Ox*tmp86);
		const double tmp235 = (Oy*tmp85);
		const double tmp232 = (Oz*tmp84);
		const double tmp82 = (St*tmp22);
		const double tmp229 = (Ox*tmp82);
		const double tmp227 = (St*tmp81);
		const double tmp226 = (tmp132*tmp21);
		const double tmp78 = (St*tmp20);
		const double tmp225 = (Oy*tmp78);
		const double tmp223 = (St*tmp77);
		const double tmp222 = (tmp132*tmp19);
		const double tmp213 = (Oz*tmp69);
		const double tmp200 = (St*tmp66);
		const double tmp64 = (Oz*tmp16);
		const double tmp196 = (Ox*tmp64);
		const double tmp192 = (Oz*tmp62);
		const double tmp190 = (Ox*tmp61);
		const double tmp59 = (St*tmp15);
		const double tmp187 = (Oz*tmp59);
		const double tmp185 = (St*tmp58);
		const double tmp56 = (Oz*tmp14);
		const double tmp184 = (Oy*tmp56);
		const double tmp180 = (Oz*tmp54);
		const double tmp178 = (Oy*tmp53);
		const double tmp51 = (St*tmp13);
		const double tmp175 = (Oz*tmp51);
		const double tmp173 = (St*tmp50);
		const double tmp170 = (tmp171*tmp4);
		const double tmp168 = (tmp169*tmp4);
		const double tmp166 = (tmp167*tmp4);
		const double tmp164 = (tmp165*tmp4);
		const double tmp162 = (tmp163*tmp4);
		const double tmp157 = (tmp132*tmp4);
		const double tmp156 = (Ox*tmp44);
		const double tmp152 = (Oy*tmp43);
		const double tmp148 = (Oz*tmp42);
		const double tmp40 = (St*tmp9);
		const double tmp144 = (Ox*tmp40);
		const double tmp142 = (St*tmp39);
		const double tmp141 = (tmp132*tmp7);
		const double tmp36 = (St*tmp6);
		const double tmp140 = (Oy*tmp36);
		const double tmp138 = (St*tmp35);
		const double tmp137 = (tmp132*tmp3);
		const double tmp32 = (St*tmp2);
		const double tmp136 = (Oz*tmp32);
		const double tmp134 = (St*tmp31);
		const double tmp131 = (tmp132*tmp1);
		const double tmp111 = (Ox*tmp27);
		const double tmp108 = (St*tmp26);
		const double tmp94 = (Oy*tmp23);
		const double tmp83 = (Ox*tmp22);
		const double tmp80 = (St*tmp21);
		const double tmp79 = (Oy*tmp20);
		const double tmp76 = (St*tmp19);
		const double tmp60 = (Oz*tmp15);
		const double tmp52 = (Oz*tmp13);
		const double tmp41 = (Ox*tmp9);
		const double tmp38 = (St*tmp7);
		const double tmp37 = (Oy*tmp6);
		const double tmp34 = (St*tmp3);
		const double tmp33 = (Oz*tmp2);
		const double tmp30 = (St*tmp1);
		const double tmp346 = (Oy*Sx);
		const double tmp345 = (Oz*Sx);
		const double tmp343 = (Oz*Sy);
		const double tmp337 = (tmp171*Vx);
		const double tmp125 = (Oy*Vx);
		const double tmp336 = (Ox*tmp125);
		const double tmp124 = (Oz*Vx);
		const double tmp334 = (Ox*tmp124);
		const double tmp329 = (Oy*tmp123);
		const double tmp328 = (Oz*tmp123);
		const double tmp326 = (Ox*tmp122);
		const double tmp325 = (Oy*tmp122);
		const double tmp324 = (Oz*tmp122);
		const double tmp321 = (Ox*tmp121);
		const double tmp316 = (Ox*tmp120);
		const double tmp304 = (Ox*tmp115);
		const double tmp303 = (Oy*tmp115);
		const double tmp302 = (Oz*tmp115);
		const double tmp287 = (tmp171*Vy);
		const double tmp285 = (Ox*tmp105);
		const double tmp284 = (tmp169*Vy);
		const double tmp104 = (Oz*Vy);
		const double tmp283 = (Oy*tmp104);
		const double tmp278 = (Oz*tmp103);
		const double tmp277 = (Ox*tmp102);
		const double tmp272 = (Ox*tmp101);
		const double tmp271 = (Oy*tmp101);
		const double tmp270 = (Oz*tmp101);
		const double tmp266 = (Oy*tmp100);
		const double tmp260 = (Ox*tmp97);
		const double tmp242 = (Ox*tmp87);
		const double tmp241 = (Oy*tmp87);
		const double tmp240 = (Oz*tmp87);
		const double tmp221 = (tmp171*Vz);
		const double tmp220 = (tmp169*Vz);
		const double tmp218 = (Ox*tmp71);
		const double tmp217 = (Oy*tmp71);
		const double tmp216 = (tmp167*Vz);
		const double tmp212 = (Ox*tmp68);
		const double tmp208 = (Oy*tmp67);
		const double tmp203 = (Ox*tmp66);
		const double tmp202 = (Oy*tmp66);
		const double tmp201 = (Oz*tmp66);
		const double tmp195 = (Ox*tmp63);
		const double tmp183 = (Oy*tmp55);
		const double tmp160 = (Ox*tmp45);
		const double tmp159 = (Oy*tmp45);
		const double tmp158 = (Oz*tmp45);
		const double tmp118 = (Ox*tmp8);
		const double tmp117 = (Oy*tmp8);
		const double tmp116 = (Oz*tmp8);
		const double tmp99 = (Ox*tmp24);
		const double tmp90 = (Ox*tmp5);
		const double tmp89 = (Oy*tmp5);
		const double tmp88 = (Oz*tmp5);
		const double tmp65 = (Ox*tmp16);
		const double tmp57 = (Oy*tmp14);
		const double tmp48 = (Ox*tmp4);
		const double tmp47 = (Oy*tmp4);
		const double tmp46 = (Oz*tmp4);
		const double tmp347 = (Ox*Sx);
		const double tmp126 = (Ox*Vx);
		const double tmp338 = (Ot*tmp126);
		const double tmp330 = (Ox*tmp123);
		const double tmp327 = (Ot*tmp122);
		const double tmp311 = (tmp133*tmp8);
		const double tmp305 = (Ot*tmp115);
		const double tmp286 = (Ot*tmp105);
		const double tmp273 = (Ot*tmp101);
		const double tmp249 = (tmp133*tmp5);
		const double tmp243 = (Ot*tmp87);
		const double tmp219 = (Ot*tmp71);
		const double tmp204 = (Ot*tmp66);
		const double tmp172 = (tmp133*tmp4);
		const double tmp161 = (Ot*tmp45);
		const double tmp106 = (Ox*Vy);
		const double tmp73 = (Ox*Vz);
		const double tmp72 = (Oy*Vz);
		const double tmp129 = (Dz*Oz);
		const double tmp128 = (Dz*Sz);
		const double tmp127 = (Ot*Vx);
		const double tmp119 = (Ot*tmp8);
		const double tmp107 = (Ot*Vy);
		const double tmp91 = (Ot*tmp5);
		const double tmp74 = (Ot*Vz);
		const double tmp75 = (Dz*tmp74);
		const double tmp70 = (Dz*tmp69);
		const double tmp49 = (Ot*tmp4);
		const double tmp18 = (Dz*Vz);
		const double e = (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((Power(Ox, 4) + (2 * (tmp171*tmp169))) + Power(Oy, 4)) + (2 * (tmp171*tmp167))) + (2 * (tmp169*tmp167))) + Power(Oz, 4)) - (2 * (tmp171*tmp165))) - (2 * (tmp169*tmp165))) - (2 * (tmp167*tmp165))) + Power(r, 4)) - (2 * (tmp171*tmp163))) - (2 * (tmp169*tmp163))) + (2 * (tmp167*tmp163))) - (2 * (tmp165*tmp163))) + Power(R, 4)) - (4 * (tmp542*Sx))) - (4 * (Ox*tmp560))) - (4 * (Ox*tmp559))) + (4 * (Ox*tmp558))) + (4 * (Ox*tmp557))) + (6 * (tmp171*tmp154))) + (2 * (tmp169*tmp154))) + (2 * (tmp167*tmp154))) - (2 * (tmp165*tmp154))) - (2 * (tmp163*tmp154))) - (4 * (Ox*tmp525))) + Power(Sx, 4)) - (4 * (tmp171*tmp344))) - (4 * (tmp490*Sy))) - (4 * (Oy*tmp556))) + (4 * (Oy*tmp555))) + (4 * (Oy*tmp554))) + (8 * (Ox*tmp553))) - (4 * (Oy*tmp552))) + (2 * (tmp171*tmp150))) + (6 * (tmp169*tmp150))) + (2 * (tmp167*tmp150))) - (2 * (tmp165*tmp150))) - (2 * (tmp163*tmp150))) - (4 * (Ox*tmp551))) + (2 * (tmp154*tmp150))) - (4 * (Oy*tmp468))) + Power(Sy, 4)) - (4 * (tmp171*tmp341))) - (4 * (tmp169*tmp341))) - (4 * (tmp425*Sz))) + (4 * (Oz*tmp550))) - (4 * (Oz*tmp549))) + (8 * (Ox*tmp548))) - (4 * (Oz*tmp547))) + (8 * (Oy*tmp546))) - (4 * (Oz*tmp545))) + (2 * (tmp171*tmp146))) + (2 * (tmp169*tmp146))) + (6 * (tmp167*tmp146))) - (2 * (tmp165*tmp146))) + (2 * (tmp163*tmp146))) - (4 * (Ox*tmp544))) + (2 * (tmp154*tmp146))) - (4 * (Oy*tmp543))) + (2 * (tmp150*tmp146))) - (4 * (Oz*tmp398))) + Power(Sz, 4)) + (4 * (Ot*tmp541))) + (4 * (Ot*tmp540))) + (4 * (Ot*tmp539))) - (4 * (Ot*tmp538))) - (4 * (Ot*tmp537))) - (4 * (tmp542*tmp123))) - (4 * (Ox*tmp536))) - (4 * (Ox*tmp535))) + (4 * (Ox*tmp534))) + (4 * (Ox*tmp533))) - (12 * (Ot*tmp532))) - (4 * (Ot*tmp531))) - (4 * (Ot*tmp530))) + (4 * (Ot*tmp529))) + (4 * (Ot*tmp528))) + (12 * (tmp171*tmp323))) + (4 * (tmp169*tmp323))) + (4 * (tmp167*tmp323))) - (4 * (tmp165*tmp323))) - (4 * (tmp163*tmp323))) + (12 * (Ot*tmp527))) - (12 * (Ox*tmp526))) - (4 * (Ot*tmp524))) + (4 * (St*tmp524))) - (8 * (Ot*tmp523))) + (8 * (Ox*tmp522))) + (8 * (Ot*tmp521))) - (8 * (Oy*tmp520))) + (4 * (Ot*tmp519))) - (4 * (Ox*tmp518))) - (4 * (Ot*tmp517))) + (4 * (St*tmp517))) - (8 * (Ot*tmp516))) + (8 * (Ox*tmp515))) + (8 * (Ot*tmp514))) - (8 * (Oz*tmp513))) + (4 * (Ot*tmp512))) - (4 * (Ox*tmp511))) - (4 * (Ot*tmp510))) + (4 * (St*tmp510))) + (6 * (tmp133*tmp310))) + (2 * (tmp133*tmp309))) + (2 * (tmp133*tmp308))) - (2 * (tmp133*tmp307))) - (2 * (tmp133*tmp306))) - (12 * (Ot*tmp509))) - (4 * (Ot*tmp508))) - (4 * (Ot*tmp507))) + (4 * (Ot*tmp506))) + (4 * (Ot*tmp505))) + (6 * (tmp171*tmp301))) + (2 * (tmp169*tmp301))) + (2 * (tmp167*tmp301))) - (2 * (tmp165*tmp301))) - (2 * (tmp163*tmp301))) - (12 * (tmp133*tmp300))) + (24 * (Ot*tmp504))) - (12 * (Ox*tmp503))) + (6 * (tmp133*tmp298))) - (12 * (Ot*tmp502))) + (6 * (tmp132*tmp298))) - (4 * (tmp133*tmp297))) + (8 * (Ot*tmp501))) - (4 * (Oy*tmp500))) + (2 * (tmp133*tmp295))) - (4 * (Ot*tmp499))) + (2 * (tmp132*tmp295))) - (4 * (tmp133*tmp294))) + (8 * (Ot*tmp498))) - (4 * (Oz*tmp497))) + (2 * (tmp133*tmp292))) - (4 * (Ot*tmp496))) + (2 * (tmp132*tmp292))) + (4 * (tmp351*tmp111))) - (12 * (tmp133*tmp291))) + (12 * (Ot*tmp495))) - (4 * (Ox*tmp494))) - (4 * (tmp351*tmp109))) + (12 * (tmp133*tmp289))) - (12 * (Ot*tmp493))) + (4 * (tmp350*tmp109))) + (tmp563*tmp26)) - (4 * (tmp351*tmp108))) + (6 * (tmp133*tmp288))) - (4 * (Ot*tmp492))) + (tmp562*tmp26)) + (4 * (Ot*tmp491))) + (4 * (Ot*tmp489))) + (4 * (Ot*tmp488))) - (4 * (Ot*tmp487))) - (4 * (Ot*tmp486))) - (4 * (tmp171*tmp279))) - (4 * (tmp490*tmp103))) - (4 * (Oy*tmp485))) + (4 * (Oy*tmp484))) + (4 * (Oy*tmp483))) - (8 * (Ot*tmp482))) + (8 * (Ox*tmp481))) + (4 * (Ot*tmp480))) - (4 * (Oy*tmp479))) - (4 * (Ot*tmp478))) - (12 * (Ot*tmp477))) - (4 * (Ot*tmp476))) + (4 * (Ot*tmp475))) + (4 * (Ot*tmp474))) + (4 * (tmp171*tmp269))) + (12 * (tmp169*tmp269))) + (4 * (tmp167*tmp269))) - (4 * (tmp165*tmp269))) - (4 * (tmp163*tmp269))) + (8 * (Ot*tmp473))) - (8 * (Ox*tmp472))) - (4 * (Ot*tmp471))) + (4 * (St*tmp471))) + (12 * (Ot*tmp470))) - (12 * (Oy*tmp469))) - (4 * (Ot*tmp467))) + (4 * (St*tmp467))) - (8 * (Ot*tmp466))) + (8 * (Oy*tmp465))) + (8 * (Ot*tmp464))) - (8 * (Oz*tmp463))) + (4 * (Ot*tmp462))) - (4 * (Oy*tmp461))) - (4 * (Ot*tmp460))) + (4 * (St*tmp460))) + (8 * (tmp133*tmp261))) - (16 * (Ot*tmp459))) + (8 * (Ox*tmp458))) - (8 * (tmp133*tmp257))) + (16 * (Ot*tmp457))) - (8 * (Oy*tmp456))) - (8 * (tmp133*tmp255))) + (16 * (Ot*tmp455))) - (8 * (Ox*tmp454))) + (8 * (tmp133*tmp253))) - (16 * (Ot*tmp453))) + (8 * (tmp132*tmp253))) + (4 * (tmp351*tmp94))) - (12 * (tmp133*tmp252))) + (12 * (Ot*tmp452))) - (4 * (Oy*tmp451))) - (4 * (tmp351*tmp92))) + (12 * (tmp133*tmp250))) - (12 * (Ot*tmp450))) + (4 * (tmp350*tmp92))) + (2 * (tmp133*tmp248))) + (6 * (tmp133*tmp247))) + (2 * (tmp133*tmp246))) - (2 * (tmp133*tmp245))) - (2 * (tmp133*tmp244))) - (4 * (Ot*tmp449))) - (12 * (Ot*tmp448))) - (4 * (Ot*tmp447))) + (4 * (Ot*tmp446))) + (4 * (Ot*tmp445))) + (2 * (tmp171*tmp239))) + (6 * (tmp169*tmp239))) + (2 * (tmp167*tmp239))) - (2 * (tmp165*tmp239))) - (2 * (tmp163*tmp239))) - (4 * (tmp133*tmp238))) + (8 * (Ot*tmp444))) - (4 * (Ox*tmp443))) + (2 * (tmp133*tmp236))) - (4 * (Ot*tmp442))) + (2 * (tmp132*tmp236))) - (12 * (tmp133*tmp235))) + (24 * (Ot*tmp441))) - (12 * (Oy*tmp440))) + (6 * (tmp133*tmp233))) - (12 * (Ot*tmp439))) + (6 * (tmp132*tmp233))) - (4 * (tmp133*tmp232))) + (8 * (Ot*tmp438))) - (4 * (Oz*tmp437))) + (2 * (tmp133*tmp230))) - (4 * (Ot*tmp436))) + (2 * (tmp132*tmp230))) + (4 * (tmp351*tmp83))) - (12 * (tmp133*tmp229))) + (12 * (Ot*tmp435))) - (4 * (Ox*tmp434))) - (4 * (tmp351*tmp81))) + (12 * (tmp133*tmp227))) - (12 * (Ot*tmp433))) + (4 * (tmp350*tmp81))) + (2 * (tmp563*tmp21))) - (8 * (tmp351*tmp80))) + (12 * (tmp133*tmp226))) - (8 * (Ot*tmp432))) + (2 * (tmp562*tmp21))) + (4 * (tmp351*tmp79))) - (12 * (tmp133*tmp225))) + (12 * (Ot*tmp431))) - (4 * (Oy*tmp430))) - (4 * (tmp351*tmp77))) + (12 * (tmp133*tmp223))) - (12 * (Ot*tmp429))) + (4 * (tmp350*tmp77))) + (tmp563*tmp19)) - (4 * (tmp351*tmp76))) + (6 * (tmp133*tmp222))) - (4 * (Ot*tmp428))) + (tmp562*tmp19)) + (4 * (Ot*tmp427))) + (4 * (Ot*tmp426))) + (4 * (Ot*tmp424))) - (4 * (Ot*tmp423))) + (4 * (Ot*tmp422))) - (4 * (tmp171*tmp213))) - (4 * (tmp169*tmp213))) - (4 * (tmp425*tmp69))) + (4 * (Oz*tmp421))) - (4 * (Oz*tmp420))) - (8 * (Ot*tmp419))) + (8 * (Ox*tmp418))) + (4 * (Ot*tmp417))) - (4 * (Oz*tmp416))) - (8 * (Ot*tmp415))) + (8 * (Oy*tmp414))) + (4 * (Ot*tmp413))) - (4 * (Oz*tmp412))) - (4 * (Ot*tmp411))) - (4 * (Ot*tmp410))) - (12 * (Ot*tmp409))) + (4 * (Ot*tmp408))) - (4 * (Ot*tmp407))) + (4 * (tmp171*tmp200))) + (4 * (tmp169*tmp200))) + (12 * (tmp167*tmp200))) - (4 * (tmp165*tmp200))) + (4 * (tmp163*tmp200))) + (8 * (Ot*tmp406))) - (8 * (Ox*tmp405))) - (4 * (Ot*tmp404))) + (4 * (St*tmp404))) + (8 * (Ot*tmp403))) - (8 * (Oy*tmp402))) - (4 * (Ot*tmp401))) + (4 * (St*tmp401))) + (12 * (Ot*tmp400))) - (12 * (Oz*tmp399))) - (4 * (Ot*tmp397))) + (4 * (St*tmp397))) + (8 * (tmp133*tmp196))) - (16 * (Ot*tmp396))) + (8 * (Ox*tmp395))) - (8 * (tmp133*tmp192))) + (16 * (Ot*tmp394))) - (8 * (Oz*tmp393))) - (8 * (tmp133*tmp190))) + (16 * (Ot*tmp392))) - (8 * (Ox*tmp391))) + (8 * (tmp133*tmp188))) - (16 * (Ot*tmp390))) + (8 * (tmp132*tmp188))) + (4 * (tmp351*tmp60))) - (12 * (tmp133*tmp187))) + (12 * (Ot*tmp389))) - (4 * (Oz*tmp388))) - (4 * (tmp351*tmp58))) + (12 * (tmp133*tmp185))) - (12 * (Ot*tmp387))) + (4 * (tmp350*tmp58))) + (8 * (tmp133*tmp184))) - (16 * (Ot*tmp386))) + (8 * (Oy*tmp385))) - (8 * (tmp133*tmp180))) + (16 * (Ot*tmp384))) - (8 * (Oz*tmp383))) - (8 * (tmp133*tmp178))) + (16 * (Ot*tmp382))) - (8 * (Oy*tmp381))) + (8 * (tmp133*tmp176))) - (16 * (Ot*tmp380))) + (8 * (tmp132*tmp176))) + (4 * (tmp351*tmp52))) - (12 * (tmp133*tmp175))) + (12 * (Ot*tmp379))) - (4 * (Oz*tmp378))) - (4 * (tmp351*tmp50))) + (12 * (tmp133*tmp173))) - (12 * (Ot*tmp377))) + (4 * (tmp350*tmp50))) + (2 * (tmp133*tmp170))) + (2 * (tmp133*tmp168))) + (6 * (tmp133*tmp166))) - (2 * (tmp133*tmp164))) + (2 * (tmp133*tmp162))) - (4 * (Ot*tmp376))) - (4 * (Ot*tmp375))) - (12 * (Ot*tmp374))) + (4 * (Ot*tmp373))) - (4 * (Ot*tmp372))) + (2 * (tmp171*tmp157))) + (2 * (tmp169*tmp157))) + (6 * (tmp167*tmp157))) - (2 * (tmp165*tmp157))) + (2 * (tmp163*tmp157))) - (4 * (tmp133*tmp156))) + (8 * (Ot*tmp371))) - (4 * (Ox*tmp370))) + (2 * (tmp133*tmp153))) - (4 * (Ot*tmp369))) + (2 * (tmp132*tmp153))) - (4 * (tmp133*tmp152))) + (8 * (Ot*tmp368))) - (4 * (Oy*tmp367))) + (2 * (tmp133*tmp149))) - (4 * (Ot*tmp366))) + (2 * (tmp132*tmp149))) - (12 * (tmp133*tmp148))) + (24 * (Ot*tmp365))) - (12 * (Oz*tmp364))) + (6 * (tmp133*tmp145))) - (12 * (Ot*tmp363))) + (6 * (tmp132*tmp145))) + (4 * (tmp351*tmp41))) - (12 * (tmp133*tmp144))) + (12 * (Ot*tmp362))) - (4 * (Ox*tmp361))) - (4 * (tmp351*tmp39))) + (12 * (tmp133*tmp142))) - (12 * (Ot*tmp360))) + (4 * (tmp350*tmp39))) + (2 * (tmp563*tmp7))) - (8 * (tmp351*tmp38))) + (12 * (tmp133*tmp141))) - (8 * (Ot*tmp359))) + (2 * (tmp562*tmp7))) + (4 * (tmp351*tmp37))) - (12 * (tmp133*tmp140))) + (12 * (Ot*tmp358))) - (4 * (Oy*tmp357))) - (4 * (tmp351*tmp35))) + (12 * (tmp133*tmp138))) - (12 * (Ot*tmp356))) + (4 * (tmp350*tmp35))) + (2 * (tmp563*tmp3))) - (8 * (tmp351*tmp34))) + (12 * (tmp133*tmp137))) - (8 * (Ot*tmp355))) + (2 * (tmp562*tmp3))) + (4 * (tmp351*tmp33))) - (12 * (tmp133*tmp136))) + (12 * (Ot*tmp354))) - (4 * (Oz*tmp353))) - (4 * (tmp351*tmp31))) + (12 * (tmp133*tmp134))) - (12 * (Ot*tmp352))) + (4 * (tmp350*tmp31))) + (tmp563*tmp1)) - (4 * (tmp351*tmp30))) + (6 * (tmp133*tmp131))) - (4 * (Ot*tmp349))) + (tmp562*tmp1));
		const double d = ((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((4 * (Dx*tmp542)) + (4 * (Dy*(tmp171*Oy)))) + (4 * (Dx*(Ox*tmp169)))) + (4 * (Dy*tmp490))) + (4 * (Dz*(tmp171*Oz)))) + (4 * (Dz*(tmp169*Oz)))) + (4 * (Dx*(Ox*tmp167)))) + (4 * (Dy*(Oy*tmp167)))) + (4 * (Dz*tmp425))) - (4 * (Dx*(Ox*tmp165)))) - (4 * (Dy*(Oy*tmp165)))) - (4 * (Dz*(Oz*tmp165)))) - (4 * (Dx*(Ox*tmp163)))) - (4 * (Dy*(Oy*tmp163)))) + (4 * (Dz*(Oz*tmp163)))) - (12 * (Dx*(tmp171*Sx)))) - (8 * (Dy*(Ox*tmp346)))) - (4 * (Dx*tmp560))) - (8 * (Dz*(Ox*tmp345)))) - (4 * (Dx*tmp559))) + (4 * (Dx*tmp558))) + (4 * (Dx*tmp557))) + (12 * (Dx*(Ox*tmp154)))) + (4 * (Dy*(Oy*tmp154)))) + (4 * (Dz*(Oz*tmp154)))) - (4 * (Dx*tmp525))) - (4 * (Dy*(tmp171*Sy)))) - (8 * (Dx*(Ox*tmp344)))) - (12 * (Dy*(tmp169*Sy)))) - (8 * (Dz*(Oy*tmp343)))) - (4 * (Dy*tmp556))) + (4 * (Dy*tmp555))) + (4 * (Dy*tmp554))) + (8 * (Dy*(Ox*tmp342)))) + (8 * (Dx*tmp553))) - (4 * (Dy*tmp552))) + (4 * (Dx*(Ox*tmp150)))) + (12 * (Dy*(Oy*tmp150)))) + (4 * (Dz*(Oz*tmp150)))) - (4 * (Dx*tmp551))) - (4 * (Dy*tmp468))) - (4 * (Dz*(tmp171*Sz)))) - (4 * (Dz*(tmp169*Sz)))) - (8 * (Dx*(Ox*tmp341)))) - (8 * (Dy*(Oy*tmp341)))) - (12 * (Dz*(tmp167*Sz)))) + (4 * (Dz*tmp550))) - (4 * (Dz*tmp549))) + (8 * (Dz*(Ox*tmp340)))) + (8 * (Dx*tmp548))) - (4 * (Dz*tmp547))) + (8 * (Dz*(Oy*tmp339)))) + (8 * (Dy*tmp546))) - (4 * (Dz*tmp545))) + (4 * (Dx*(Ox*tmp146)))) + (4 * (Dy*(Oy*tmp146)))) + (12 * (Dz*(Oz*tmp146)))) - (4 * (Dx*tmp544))) - (4 * (Dy*tmp543))) - (4 * (Dz*tmp398))) + (12 * (Dx*(Ot*tmp337)))) - (4 * tmp541)) + (8 * (Dy*(Ot*tmp336)))) + (4 * (Dx*(Ot*tmp335)))) - (4 * tmp540)) + (8 * (Dz*(Ot*tmp334)))) + (4 * (Dx*(Ot*tmp333)))) - (4 * tmp539)) - (4 * (Dx*(Ot*tmp332)))) + (4 * tmp538)) - (4 * (Dx*(Ot*tmp331)))) + (4 * tmp537)) - (12 * (Dx*(tmp171*tmp123)))) - (8 * (Dy*(Ox*tmp329)))) - (4 * (Dx*tmp536))) - (8 * (Dz*(Ox*tmp328)))) - (4 * (Dx*tmp535))) + (4 * (Dx*tmp534))) + (4 * (Dx*tmp533))) - (24 * (Dx*(Ot*tmp326)))) + (12 * tmp532)) - (8 * (Dy*(Ot*tmp325)))) + (4 * tmp531)) - (8 * (Dz*(Ot*tmp324)))) + (4 * tmp530)) - (4 * tmp529)) - (4 * tmp528)) + (24 * (Dx*(Ox*tmp323)))) + (8 * (Dy*(Oy*tmp323)))) + (8 * (Dz*(Oz*tmp323)))) + (12 * (Dx*(Ot*tmp322)))) - (12 * tmp527)) - (12 * (Dx*tmp526))) + (4 * tmp524)) - (8 * (Dy*(Ot*tmp321)))) - (8 * (Dx*(Ot*tmp320)))) + (8 * tmp523)) + (8 * (Dy*(Ox*tmp319)))) + (8 * (Dx*tmp522))) + (8 * (Dy*(Ot*tmp318)))) - (8 * tmp521)) - (8 * (Dy*tmp520))) + (4 * (Dx*(Ot*tmp317)))) - (4 * tmp519)) - (4 * (Dx*tmp518))) + (4 * tmp517)) - (8 * (Dz*(Ot*tmp316)))) - (8 * (Dx*(Ot*tmp315)))) + (8 * tmp516)) + (8 * (Dz*(Ox*tmp314)))) + (8 * (Dx*tmp515))) + (8 * (Dz*(Ot*tmp313)))) - (8 * tmp514)) - (8 * (Dz*tmp513))) + (4 * (Dx*(Ot*tmp312)))) - (4 * tmp512)) - (4 * (Dx*tmp511))) + (4 * tmp510)) + (12 * (Dx*(tmp133*tmp118)))) - (12 * (Ot*tmp310))) + (4 * (Dy*(tmp133*tmp117)))) - (4 * (Ot*tmp309))) + (4 * (Dz*(tmp133*tmp116)))) - (4 * (Ot*tmp308))) + (4 * (Ot*tmp307))) + (4 * (Ot*tmp306))) - (24 * (Dx*(Ot*tmp304)))) + (12 * tmp509)) - (8 * (Dy*(Ot*tmp303)))) + (4 * tmp508)) - (8 * (Dz*(Ot*tmp302)))) + (4 * tmp507)) - (4 * tmp506)) - (4 * tmp505)) + (12 * (Dx*(Ox*tmp301)))) + (4 * (Dy*(Oy*tmp301)))) + (4 * (Dz*(Oz*tmp301)))) - (12 * (Dx*(tmp133*tmp114)))) + (24 * (Ot*tmp300))) + (24 * (Dx*(Ot*tmp299)))) - (24 * tmp504)) - (12 * (Dx*tmp503))) - (12 * (Ot*tmp298))) + (12 * tmp502)) - (4 * (Dy*(tmp133*tmp113)))) + (8 * (Ot*tmp297))) + (8 * (Dy*(Ot*tmp296)))) - (8 * tmp501)) - (4 * (Dy*tmp500))) - (4 * (Ot*tmp295))) + (4 * tmp499)) - (4 * (Dz*(tmp133*tmp112)))) + (8 * (Ot*tmp294))) + (8 * (Dz*(Ot*tmp293)))) - (8 * tmp498)) - (4 * (Dz*tmp497))) - (4 * (Ot*tmp292))) + (4 * tmp496)) + (4 * (Dx*(tmp351*tmp27)))) - (12 * (tmp133*tmp111))) - (12 * (Dx*(tmp133*tmp110)))) + (24 * (Ot*tmp291))) + (12 * (Dx*(Ot*tmp290)))) - (12 * tmp495)) - (4 * (Dx*tmp494))) + (12 * (tmp133*tmp109))) - (24 * (Ot*tmp289))) + (12 * tmp493)) - (4 * (tmp351*tmp26))) + (12 * (tmp133*tmp108))) - (12 * (Ot*tmp288))) + (4 * tmp492)) + (4 * (Dy*(Ot*tmp287)))) + (8 * (Dx*(Ot*tmp285)))) - (4 * tmp491)) + (12 * (Dy*(Ot*tmp284)))) - (4 * tmp489)) + (8 * (Dz*(Ot*tmp283)))) + (4 * (Dy*(Ot*tmp282)))) - (4 * tmp488)) - (4 * (Dy*(Ot*tmp281)))) + (4 * tmp487)) - (4 * (Dy*(Ot*tmp280)))) + (4 * tmp486)) - (4 * (Dy*(tmp171*tmp103)))) - (8 * (Dx*(Ox*tmp279)))) - (12 * (Dy*(tmp169*tmp103)))) - (8 * (Dz*(Oy*tmp278)))) - (4 * (Dy*tmp485))) + (4 * (Dy*tmp484))) + (4 * (Dy*tmp483))) - (8 * (Dy*(Ot*tmp277)))) - (8 * (Dx*(Ot*tmp276)))) + (8 * tmp482)) + (8 * (Dy*(Ox*tmp275)))) + (8 * (Dx*tmp481))) + (4 * (Dy*(Ot*tmp274)))) - (4 * tmp480)) - (4 * (Dy*tmp479))) - (8 * (Dx*(Ot*tmp272)))) + (4 * tmp478)) - (24 * (Dy*(Ot*tmp271)))) + (12 * tmp477)) - (8 * (Dz*(Ot*tmp270)))) + (4 * tmp476)) - (4 * tmp475)) - (4 * tmp474)) + (8 * (Dx*(Ox*tmp269)))) + (24 * (Dy*(Oy*tmp269)))) + (8 * (Dz*(Oz*tmp269)))) + (8 * (Dx*(Ot*tmp268)))) - (8 * tmp473)) - (8 * (Dx*tmp472))) + (4 * tmp471)) + (12 * (Dy*(Ot*tmp267)))) - (12 * tmp470)) - (12 * (Dy*tmp469))) + (4 * tmp467)) - (8 * (Dz*(Ot*tmp266)))) - (8 * (Dy*(Ot*tmp265)))) + (8 * tmp466)) + (8 * (Dz*(Oy*tmp264)))) + (8 * (Dy*tmp465))) + (8 * (Dz*(Ot*tmp263)))) - (8 * tmp464)) - (8 * (Dz*tmp463))) + (4 * (Dy*(Ot*tmp262)))) - (4 * tmp462)) - (4 * (Dy*tmp461))) + (4 * tmp460)) + (8 * (Dy*(tmp133*tmp99)))) + (8 * (Dx*(tmp133*tmp98)))) - (16 * (Ot*tmp261))) - (16 * (Dy*(Ot*tmp260)))) - (16 * (Dx*(Ot*tmp259)))) + (16 * tmp459)) + (8 * (Dy*(Ox*tmp258)))) + (8 * (Dx*tmp458))) - (8 * (Dy*(tmp133*tmp96)))) + (16 * (Ot*tmp257))) + (16 * (Dy*(Ot*tmp256)))) - (16 * tmp457)) - (8 * (Dy*tmp456))) - (8 * (Dx*(tmp133*tmp95)))) + (16 * (Ot*tmp255))) + (16 * (Dx*(Ot*tmp254)))) - (16 * tmp455)) - (8 * (Dx*tmp454))) - (16 * (Ot*tmp253))) + (16 * tmp453)) + (4 * (Dy*(tmp351*tmp23)))) - (12 * (tmp133*tmp94))) - (12 * (Dy*(tmp133*tmp93)))) + (24 * (Ot*tmp252))) + (12 * (Dy*(Ot*tmp251)))) - (12 * tmp452)) - (4 * (Dy*tmp451))) + (12 * (tmp133*tmp92))) - (24 * (Ot*tmp250))) + (12 * tmp450)) + (4 * (Dx*(tmp133*tmp90)))) - (4 * (Ot*tmp248))) + (12 * (Dy*(tmp133*tmp89)))) - (12 * (Ot*tmp247))) + (4 * (Dz*(tmp133*tmp88)))) - (4 * (Ot*tmp246))) + (4 * (Ot*tmp245))) + (4 * (Ot*tmp244))) - (8 * (Dx*(Ot*tmp242)))) + (4 * tmp449)) - (24 * (Dy*(Ot*tmp241)))) + (12 * tmp448)) - (8 * (Dz*(Ot*tmp240)))) + (4 * tmp447)) - (4 * tmp446)) - (4 * tmp445)) + (4 * (Dx*(Ox*tmp239)))) + (12 * (Dy*(Oy*tmp239)))) + (4 * (Dz*(Oz*tmp239)))) - (4 * (Dx*(tmp133*tmp86)))) + (8 * (Ot*tmp238))) + (8 * (Dx*(Ot*tmp237)))) - (8 * tmp444)) - (4 * (Dx*tmp443))) - (4 * (Ot*tmp236))) + (4 * tmp442)) - (12 * (Dy*(tmp133*tmp85)))) + (24 * (Ot*tmp235))) + (24 * (Dy*(Ot*tmp234)))) - (24 * tmp441)) - (12 * (Dy*tmp440))) - (12 * (Ot*tmp233))) + (12 * tmp439)) - (4 * (Dz*(tmp133*tmp84)))) + (8 * (Ot*tmp232))) + (8 * (Dz*(Ot*tmp231)))) - (8 * tmp438)) - (4 * (Dz*tmp437))) - (4 * (Ot*tmp230))) + (4 * tmp436)) + (4 * (Dx*(tmp351*tmp22)))) - (12 * (tmp133*tmp83))) - (12 * (Dx*(tmp133*tmp82)))) + (24 * (Ot*tmp229))) + (12 * (Dx*(Ot*tmp228)))) - (12 * tmp435)) - (4 * (Dx*tmp434))) + (12 * (tmp133*tmp81))) - (24 * (Ot*tmp227))) + (12 * tmp433)) - (8 * (tmp351*tmp21))) + (24 * (tmp133*tmp80))) - (24 * (Ot*tmp226))) + (8 * tmp432)) + (4 * (Dy*(tmp351*tmp20)))) - (12 * (tmp133*tmp79))) - (12 * (Dy*(tmp133*tmp78)))) + (24 * (Ot*tmp225))) + (12 * (Dy*(Ot*tmp224)))) - (12 * tmp431)) - (4 * (Dy*tmp430))) + (12 * (tmp133*tmp77))) - (24 * (Ot*tmp223))) + (12 * tmp429)) - (4 * (tmp351*tmp19))) + (12 * (tmp133*tmp76))) - (12 * (Ot*tmp222))) + (4 * tmp428)) + (4 * (Dz*(Ot*tmp221)))) + (4 * (Dz*(Ot*tmp220)))) + (8 * (Dx*(Ot*tmp218)))) - (4 * tmp427)) + (8 * (Dy*(Ot*tmp217)))) - (4 * tmp426)) + (12 * (Dz*(Ot*tmp216)))) - (4 * tmp424)) - (4 * (Dz*(Ot*tmp215)))) + (4 * tmp423)) + (4 * (Dz*(Ot*tmp214)))) - (4 * tmp422)) - (4 * (Dz*(tmp171*tmp69)))) - (4 * (Dz*(tmp169*tmp69)))) - (8 * (Dx*(Ox*tmp213)))) - (8 * (Dy*(Oy*tmp213)))) - (12 * (Dz*(tmp167*tmp69)))) + (4 * (Dz*tmp421))) - (4 * (Dz*tmp420))) - (8 * (Dz*(Ot*tmp212)))) - (8 * (Dx*(Ot*tmp211)))) + (8 * tmp419)) + (8 * (Dz*(Ox*tmp210)))) + (8 * (Dx*tmp418))) + (4 * (Dz*(Ot*tmp209)))) - (4 * tmp417)) - (4 * (Dz*tmp416))) - (8 * (Dz*(Ot*tmp208)))) - (8 * (Dy*(Ot*tmp207)))) + (8 * tmp415)) + (8 * (Dz*(Oy*tmp206)))) + (8 * (Dy*tmp414))) + (4 * (Dz*(Ot*tmp205)))) - (4 * tmp413)) - (4 * (Dz*tmp412))) - (8 * (Dx*(Ot*tmp203)))) + (4 * tmp411)) - (8 * (Dy*(Ot*tmp202)))) + (4 * tmp410)) - (24 * (Dz*(Ot*tmp201)))) + (12 * tmp409)) - (4 * tmp408)) + (4 * tmp407)) + (8 * (Dx*(Ox*tmp200)))) + (8 * (Dy*(Oy*tmp200)))) + (24 * (Dz*(Oz*tmp200)))) + (8 * (Dx*(Ot*tmp199)))) - (8 * tmp406)) - (8 * (Dx*tmp405))) + (4 * tmp404)) + (8 * (Dy*(Ot*tmp198)))) - (8 * tmp403)) - (8 * (Dy*tmp402))) + (4 * tmp401)) + (12 * (Dz*(Ot*tmp197)))) - (12 * tmp400)) - (12 * (Dz*tmp399))) + (4 * tmp397)) + (8 * (Dz*(tmp133*tmp65)))) + (8 * (Dx*(tmp133*tmp64)))) - (16 * (Ot*tmp196))) - (16 * (Dz*(Ot*tmp195)))) - (16 * (Dx*(Ot*tmp194)))) + (16 * tmp396)) + (8 * (Dz*(Ox*tmp193)))) + (8 * (Dx*tmp395))) - (8 * (Dz*(tmp133*tmp62)))) + (16 * (Ot*tmp192))) + (16 * (Dz*(Ot*tmp191)))) - (16 * tmp394)) - (8 * (Dz*tmp393))) - (8 * (Dx*(tmp133*tmp61)))) + (16 * (Ot*tmp190))) + (16 * (Dx*(Ot*tmp189)))) - (16 * tmp392)) - (8 * (Dx*tmp391))) - (16 * (Ot*tmp188))) + (16 * tmp390)) + (4 * (Dz*(tmp351*tmp15)))) - (12 * (tmp133*tmp60))) - (12 * (Dz*(tmp133*tmp59)))) + (24 * (Ot*tmp187))) + (12 * (Dz*(Ot*tmp186)))) - (12 * tmp389)) - (4 * (Dz*tmp388))) + (12 * (tmp133*tmp58))) - (24 * (Ot*tmp185))) + (12 * tmp387)) + (8 * (Dz*(tmp133*tmp57)))) + (8 * (Dy*(tmp133*tmp56)))) - (16 * (Ot*tmp184))) - (16 * (Dz*(Ot*tmp183)))) - (16 * (Dy*(Ot*tmp182)))) + (16 * tmp386)) + (8 * (Dz*(Oy*tmp181)))) + (8 * (Dy*tmp385))) - (8 * (Dz*(tmp133*tmp54)))) + (16 * (Ot*tmp180))) + (16 * (Dz*(Ot*tmp179)))) - (16 * tmp384)) - (8 * (Dz*tmp383))) - (8 * (Dy*(tmp133*tmp53)))) + (16 * (Ot*tmp178))) + (16 * (Dy*(Ot*tmp177)))) - (16 * tmp382)) - (8 * (Dy*tmp381))) - (16 * (Ot*tmp176))) + (16 * tmp380)) + (4 * (Dz*(tmp351*tmp13)))) - (12 * (tmp133*tmp52))) - (12 * (Dz*(tmp133*tmp51)))) + (24 * (Ot*tmp175))) + (12 * (Dz*(Ot*tmp174)))) - (12 * tmp379)) - (4 * (Dz*tmp378))) + (12 * (tmp133*tmp50))) - (24 * (Ot*tmp173))) + (12 * tmp377)) + (4 * (Dx*(tmp133*tmp48)))) - (4 * (Ot*tmp170))) + (4 * (Dy*(tmp133*tmp47)))) - (4 * (Ot*tmp168))) + (12 * (Dz*(tmp133*tmp46)))) - (12 * (Ot*tmp166))) + (4 * (Ot*tmp164))) - (4 * (Ot*tmp162))) - (8 * (Dx*(Ot*tmp160)))) + (4 * tmp376)) - (8 * (Dy*(Ot*tmp159)))) + (4 * tmp375)) - (24 * (Dz*(Ot*tmp158)))) + (12 * tmp374)) - (4 * tmp373)) + (4 * tmp372)) + (4 * (Dx*(Ox*tmp157)))) + (4 * (Dy*(Oy*tmp157)))) + (12 * (Dz*(Oz*tmp157)))) - (4 * (Dx*(tmp133*tmp44)))) + (8 * (Ot*tmp156))) + (8 * (Dx*(Ot*tmp155)))) - (8 * tmp371)) - (4 * (Dx*tmp370))) - (4 * (Ot*tmp153))) + (4 * tmp369)) - (4 * (Dy*(tmp133*tmp43)))) + (8 * (Ot*tmp152))) + (8 * (Dy*(Ot*tmp151)))) - (8 * tmp368)) - (4 * (Dy*tmp367))) - (4 * (Ot*tmp149))) + (4 * tmp366)) - (12 * (Dz*(tmp133*tmp42)))) + (24 * (Ot*tmp148))) + (24 * (Dz*(Ot*tmp147)))) - (24 * tmp365)) - (12 * (Dz*tmp364))) - (12 * (Ot*tmp145))) + (12 * tmp363)) + (4 * (Dx*(tmp351*tmp9)))) - (12 * (tmp133*tmp41))) - (12 * (Dx*(tmp133*tmp40)))) + (24 * (Ot*tmp144))) + (12 * (Dx*(Ot*tmp143)))) - (12 * tmp362)) - (4 * (Dx*tmp361))) + (12 * (tmp133*tmp39))) - (24 * (Ot*tmp142))) + (12 * tmp360)) - (8 * (tmp351*tmp7))) + (24 * (tmp133*tmp38))) - (24 * (Ot*tmp141))) + (8 * tmp359)) + (4 * (Dy*(tmp351*tmp6)))) - (12 * (tmp133*tmp37))) - (12 * (Dy*(tmp133*tmp36)))) + (24 * (Ot*tmp140))) + (12 * (Dy*(Ot*tmp139)))) - (12 * tmp358)) - (4 * (Dy*tmp357))) + (12 * (tmp133*tmp35))) - (24 * (Ot*tmp138))) + (12 * tmp356)) - (8 * (tmp351*tmp3))) + (24 * (tmp133*tmp34))) - (24 * (Ot*tmp137))) + (8 * tmp355)) + (4 * (Dz*(tmp351*tmp2)))) - (12 * (tmp133*tmp33))) - (12 * (Dz*(tmp133*tmp32)))) + (24 * (Ot*tmp136))) + (12 * (Dz*(Ot*tmp135)))) - (12 * tmp354)) - (4 * (Dz*tmp353))) + (12 * (tmp133*tmp31))) - (24 * (Ot*tmp134))) + (12 * tmp352)) - (4 * (tmp351*tmp1))) + (12 * (tmp133*tmp30))) - (12 * (Ot*tmp131))) + (4 * tmp349));
		const double c = ((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((6 * (tmp12*tmp171)) + (2 * (tmp11*tmp171))) + (2 * (tmp10*tmp171))) + (8 * (Dx*(Dy*(Ox*Oy))))) + (2 * (tmp12*tmp169))) + (6 * (tmp11*tmp169))) + (2 * (tmp10*tmp169))) + (8 * (Dx*(Dz*(Ox*Oz))))) + (8 * (Dy*(Dz*(Oy*Oz))))) + (2 * (tmp12*tmp167))) + (2 * (tmp11*tmp167))) + (6 * (tmp10*tmp167))) - (2 * (tmp12*tmp165))) - (2 * (tmp11*tmp165))) - (2 * (tmp10*tmp165))) - (2 * (tmp12*tmp163))) - (2 * (tmp11*tmp163))) + (2 * (tmp10*tmp163))) - (12 * (tmp12*tmp347))) - (4 * (tmp11*tmp347))) - (4 * (tmp10*tmp347))) - (8 * (Dx*(Dy*tmp346)))) - (8 * (Dx*(Dz*tmp345)))) + (6 * (tmp12*tmp154))) + (2 * (tmp11*tmp154))) + (2 * (tmp10*tmp154))) - (8 * (Dx*(Dy*(Ox*Sy))))) - (4 * (tmp12*tmp344))) - (12 * (tmp11*tmp344))) - (4 * (tmp10*tmp344))) - (8 * (Dy*(Dz*tmp343)))) + (8 * (Dx*(Dy*tmp342)))) + (2 * (tmp12*tmp150))) + (6 * (tmp11*tmp150))) + (2 * (tmp10*tmp150))) - (8 * (Dx*(Dz*(Ox*Sz))))) - (8 * (Dy*(Dz*(Oy*Sz))))) - (4 * (tmp12*tmp341))) - (4 * (tmp11*tmp341))) - (12 * (tmp10*tmp341))) + (8 * (Dx*(Dz*tmp340)))) + (8 * (Dy*(Dz*tmp339)))) + (2 * (tmp12*tmp146))) + (2 * (tmp11*tmp146))) + (6 * (tmp10*tmp146))) + (12 * (tmp12*tmp338))) + (4 * (tmp11*tmp338))) + (4 * (tmp10*tmp338))) - (12 * (Dx*tmp337))) + (8 * (Dx*(Dy*(Ot*tmp125))))) - (8 * (Dy*tmp336))) - (4 * (Dx*tmp335))) + (8 * (Dx*(Dz*(Ot*tmp124))))) - (8 * (Dz*tmp334))) - (4 * (Dx*tmp333))) + (4 * (Dx*tmp332))) + (4 * (Dx*tmp331))) - (12 * (tmp12*tmp330))) - (4 * (tmp11*tmp330))) - (4 * (tmp10*tmp330))) - (8 * (Dx*(Dy*tmp329)))) - (8 * (Dx*(Dz*tmp328)))) - (12 * (tmp12*tmp327))) - (4 * (tmp11*tmp327))) - (4 * (tmp10*tmp327))) + (24 * (Dx*tmp326))) + (8 * (Dy*tmp325))) + (8 * (Dz*tmp324))) + (12 * (tmp12*tmp323))) + (4 * (tmp11*tmp323))) + (4 * (tmp10*tmp323))) - (12 * (Dx*tmp322))) - (8 * (Dx*(Dy*(Ot*tmp121))))) + (8 * (Dy*tmp321))) + (8 * (Dx*tmp320))) + (8 * (Dx*(Dy*tmp319)))) - (8 * (Dy*tmp318))) - (4 * (Dx*tmp317))) - (8 * (Dx*(Dz*(Ot*tmp120))))) + (8 * (Dz*tmp316))) + (8 * (Dx*tmp315))) + (8 * (Dx*(Dz*tmp314)))) - (8 * (Dz*tmp313))) - (4 * (Dx*tmp312))) + (6 * (tmp12*tmp311))) + (2 * (tmp11*tmp311))) + (2 * (tmp10*tmp311))) - (24 * (Dx*(Ot*tmp118)))) + (6 * tmp310)) - (8 * (Dy*(Ot*tmp117)))) + (2 * tmp309)) - (8 * (Dz*(Ot*tmp116)))) + (2 * tmp308)) - (2 * tmp307)) - (2 * tmp306)) - (12 * (tmp12*tmp305))) - (4 * (tmp11*tmp305))) - (4 * (tmp10*tmp305))) + (24 * (Dx*tmp304))) + (8 * (Dy*tmp303))) + (8 * (Dz*tmp302))) + (6 * (tmp12*tmp301))) + (2 * (tmp11*tmp301))) + (2 * (tmp10*tmp301))) + (24 * (Dx*(Ot*tmp114)))) - (12 * tmp300)) - (24 * (Dx*tmp299))) + (6 * tmp298)) + (8 * (Dy*(Ot*tmp113)))) - (4 * tmp297)) - (8 * (Dy*tmp296))) + (2 * tmp295)) + (8 * (Dz*(Ot*tmp112)))) - (4 * tmp294)) - (8 * (Dz*tmp293))) + (2 * tmp292)) - (12 * (Dx*(tmp133*tmp27)))) + (12 * (Ot*tmp111))) + (24 * (Dx*(Ot*tmp110)))) - (12 * tmp291)) - (12 * (Dx*tmp290))) - (12 * (Ot*tmp109))) + (12 * tmp289)) + (6 * (tmp133*tmp26))) - (12 * (Ot*tmp108))) + (6 * tmp288)) + (8 * (Dx*(Dy*(Ot*tmp106))))) - (4 * (Dy*tmp287))) + (4 * (tmp12*tmp286))) + (12 * (tmp11*tmp286))) + (4 * (tmp10*tmp286))) - (8 * (Dx*tmp285))) - (12 * (Dy*tmp284))) + (8 * (Dy*(Dz*(Ot*tmp104))))) - (8 * (Dz*tmp283))) - (4 * (Dy*tmp282))) + (4 * (Dy*tmp281))) + (4 * (Dy*tmp280))) - (8 * (Dx*(Dy*(Ox*tmp103))))) - (4 * (tmp12*tmp279))) - (12 * (tmp11*tmp279))) - (4 * (tmp10*tmp279))) - (8 * (Dy*(Dz*tmp278)))) - (8 * (Dx*(Dy*(Ot*tmp102))))) + (8 * (Dy*tmp277))) + (8 * (Dx*tmp276))) + (8 * (Dx*(Dy*tmp275)))) - (4 * (Dy*tmp274))) - (4 * (tmp12*tmp273))) - (12 * (tmp11*tmp273))) - (4 * (tmp10*tmp273))) + (8 * (Dx*tmp272))) + (24 * (Dy*tmp271))) + (8 * (Dz*tmp270))) + (4 * (tmp12*tmp269))) + (12 * (tmp11*tmp269))) + (4 * (tmp10*tmp269))) - (8 * (Dx*tmp268))) - (12 * (Dy*tmp267))) - (8 * (Dy*(Dz*(Ot*tmp100))))) + (8 * (Dz*tmp266))) + (8 * (Dy*tmp265))) + (8 * (Dy*(Dz*tmp264)))) - (8 * (Dz*tmp263))) - (4 * (Dy*tmp262))) + (8 * (Dx*(Dy*(tmp133*tmp24))))) - (16 * (Dy*(Ot*tmp99)))) - (16 * (Dx*(Ot*tmp98)))) + (8 * tmp261)) - (16 * (Dx*(Dy*(Ot*tmp97))))) + (16 * (Dy*tmp260))) + (16 * (Dx*tmp259))) + (8 * (Dx*(Dy*tmp258)))) + (16 * (Dy*(Ot*tmp96)))) - (8 * tmp257)) - (16 * (Dy*tmp256))) + (16 * (Dx*(Ot*tmp95)))) - (8 * tmp255)) - (16 * (Dx*tmp254))) + (8 * tmp253)) - (12 * (Dy*(tmp133*tmp23)))) + (12 * (Ot*tmp94))) + (24 * (Dy*(Ot*tmp93)))) - (12 * tmp252)) - (12 * (Dy*tmp251))) - (12 * (Ot*tmp92))) + (12 * tmp250)) + (2 * (tmp12*tmp249))) + (6 * (tmp11*tmp249))) + (2 * (tmp10*tmp249))) - (8 * (Dx*(Ot*tmp90)))) + (2 * tmp248)) - (24 * (Dy*(Ot*tmp89)))) + (6 * tmp247)) - (8 * (Dz*(Ot*tmp88)))) + (2 * tmp246)) - (2 * tmp245)) - (2 * tmp244)) - (4 * (tmp12*tmp243))) - (12 * (tmp11*tmp243))) - (4 * (tmp10*tmp243))) + (8 * (Dx*tmp242))) + (24 * (Dy*tmp241))) + (8 * (Dz*tmp240))) + (2 * (tmp12*tmp239))) + (6 * (tmp11*tmp239))) + (2 * (tmp10*tmp239))) + (8 * (Dx*(Ot*tmp86)))) - (4 * tmp238)) - (8 * (Dx*tmp237))) + (2 * tmp236)) + (24 * (Dy*(Ot*tmp85)))) - (12 * tmp235)) - (24 * (Dy*tmp234))) + (6 * tmp233)) + (8 * (Dz*(Ot*tmp84)))) - (4 * tmp232)) - (8 * (Dz*tmp231))) + (2 * tmp230)) - (12 * (Dx*(tmp133*tmp22)))) + (12 * (Ot*tmp83))) + (24 * (Dx*(Ot*tmp82)))) - (12 * tmp229)) - (12 * (Dx*tmp228))) - (12 * (Ot*tmp81))) + (12 * tmp227)) + (12 * (tmp133*tmp21))) - (24 * (Ot*tmp80))) + (12 * tmp226)) - (12 * (Dy*(tmp133*tmp20)))) + (12 * (Ot*tmp79))) + (24 * (Dy*(Ot*tmp78)))) - (12 * tmp225)) - (12 * (Dy*tmp224))) - (12 * (Ot*tmp77))) + (12 * tmp223)) + (6 * (tmp133*tmp19))) - (12 * (Ot*tmp76))) + (6 * tmp222)) + (8 * (Dx*(Dz*(Ot*tmp73))))) - (4 * (Dz*tmp221))) + (8 * (Dy*(Dz*(Ot*tmp72))))) - (4 * (Dz*tmp220))) + (4 * (tmp12*tmp219))) + (4 * (tmp11*tmp219))) + (12 * (tmp10*tmp219))) - (8 * (Dx*tmp218))) - (8 * (Dy*tmp217))) - (12 * (Dz*tmp216))) + (4 * (Dz*tmp215))) - (4 * (Dz*tmp214))) - (8 * (Dx*(Dz*(Ox*tmp69))))) - (8 * (Dy*(Dz*(Oy*tmp69))))) - (4 * (tmp12*tmp213))) - (4 * (tmp11*tmp213))) - (12 * (tmp10*tmp213))) - (8 * (Dx*(Dz*(Ot*tmp68))))) + (8 * (Dz*tmp212))) + (8 * (Dx*tmp211))) + (8 * (Dx*(Dz*tmp210)))) - (4 * (Dz*tmp209))) - (8 * (Dy*(Dz*(Ot*tmp67))))) + (8 * (Dz*tmp208))) + (8 * (Dy*tmp207))) + (8 * (Dy*(Dz*tmp206)))) - (4 * (Dz*tmp205))) - (4 * (tmp12*tmp204))) - (4 * (tmp11*tmp204))) - (12 * (tmp10*tmp204))) + (8 * (Dx*tmp203))) + (8 * (Dy*tmp202))) + (24 * (Dz*tmp201))) + (4 * (tmp12*tmp200))) + (4 * (tmp11*tmp200))) + (12 * (tmp10*tmp200))) - (8 * (Dx*tmp199))) - (8 * (Dy*tmp198))) - (12 * (Dz*tmp197))) + (8 * (Dx*(Dz*(tmp133*tmp16))))) - (16 * (Dz*(Ot*tmp65)))) - (16 * (Dx*(Ot*tmp64)))) + (8 * tmp196)) - (16 * (Dx*(Dz*(Ot*tmp63))))) + (16 * (Dz*tmp195))) + (16 * (Dx*tmp194))) + (8 * (Dx*(Dz*tmp193)))) + (16 * (Dz*(Ot*tmp62)))) - (8 * tmp192)) - (16 * (Dz*tmp191))) + (16 * (Dx*(Ot*tmp61)))) - (8 * tmp190)) - (16 * (Dx*tmp189))) + (8 * tmp188)) - (12 * (Dz*(tmp133*tmp15)))) + (12 * (Ot*tmp60))) + (24 * (Dz*(Ot*tmp59)))) - (12 * tmp187)) - (12 * (Dz*tmp186))) - (12 * (Ot*tmp58))) + (12 * tmp185)) + (8 * (Dy*(Dz*(tmp133*tmp14))))) - (16 * (Dz*(Ot*tmp57)))) - (16 * (Dy*(Ot*tmp56)))) + (8 * tmp184)) - (16 * (Dy*(Dz*(Ot*tmp55))))) + (16 * (Dz*tmp183))) + (16 * (Dy*tmp182))) + (8 * (Dy*(Dz*tmp181)))) + (16 * (Dz*(Ot*tmp54)))) - (8 * tmp180)) - (16 * (Dz*tmp179))) + (16 * (Dy*(Ot*tmp53)))) - (8 * tmp178)) - (16 * (Dy*tmp177))) + (8 * tmp176)) - (12 * (Dz*(tmp133*tmp13)))) + (12 * (Ot*tmp52))) + (24 * (Dz*(Ot*tmp51)))) - (12 * tmp175)) - (12 * (Dz*tmp174))) - (12 * (Ot*tmp50))) + (12 * tmp173)) + (2 * (tmp12*tmp172))) + (2 * (tmp11*tmp172))) + (6 * (tmp10*tmp172))) - (8 * (Dx*(Ot*tmp48)))) + (2 * tmp170)) - (8 * (Dy*(Ot*tmp47)))) + (2 * tmp168)) - (24 * (Dz*(Ot*tmp46)))) + (6 * tmp166)) - (2 * tmp164)) + (2 * tmp162)) - (4 * (tmp12*tmp161))) - (4 * (tmp11*tmp161))) - (12 * (tmp10*tmp161))) + (8 * (Dx*tmp160))) + (8 * (Dy*tmp159))) + (24 * (Dz*tmp158))) + (2 * (tmp12*tmp157))) + (2 * (tmp11*tmp157))) + (6 * (tmp10*tmp157))) + (8 * (Dx*(Ot*tmp44)))) - (4 * tmp156)) - (8 * (Dx*tmp155))) + (2 * tmp153)) + (8 * (Dy*(Ot*tmp43)))) - (4 * tmp152)) - (8 * (Dy*tmp151))) + (2 * tmp149)) + (24 * (Dz*(Ot*tmp42)))) - (12 * tmp148)) - (24 * (Dz*tmp147))) + (6 * tmp145)) - (12 * (Dx*(tmp133*tmp9)))) + (12 * (Ot*tmp41))) + (24 * (Dx*(Ot*tmp40)))) - (12 * tmp144)) - (12 * (Dx*tmp143))) - (12 * (Ot*tmp39))) + (12 * tmp142)) + (12 * (tmp133*tmp7))) - (24 * (Ot*tmp38))) + (12 * tmp141)) - (12 * (Dy*(tmp133*tmp6)))) + (12 * (Ot*tmp37))) + (24 * (Dy*(Ot*tmp36)))) - (12 * tmp140)) - (12 * (Dy*tmp139))) - (12 * (Ot*tmp35))) + (12 * tmp138)) + (12 * (tmp133*tmp3))) - (24 * (Ot*tmp34))) + (12 * tmp137)) - (12 * (Dz*(tmp133*tmp2)))) + (12 * (Ot*tmp33))) + (24 * (Dz*(Ot*tmp32)))) - (12 * tmp136)) - (12 * (Dz*tmp135))) - (12 * (Ot*tmp31))) + (12 * tmp134)) + (6 * (tmp133*tmp1))) - (12 * (Ot*tmp30))) + (6 * tmp131));
		const double b = ((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((4 * (tmp28*Ox)) + (4 * (Dx*(tmp11*Ox)))) + (4 * (Dx*(tmp10*Ox)))) + (4 * (tmp12*(Dy*Oy)))) + (4 * (tmp25*Oy))) + (4 * (Dy*(tmp10*Oy)))) + (4 * (tmp12*tmp129))) + (4 * (tmp11*tmp129))) + (4 * (tmp17*Oz))) - (4 * (tmp28*Sx))) - (4 * (Dx*(tmp11*Sx)))) - (4 * (Dx*(tmp10*Sx)))) - (4 * (tmp12*(Dy*Sy)))) - (4 * (tmp25*Sy))) - (4 * (Dy*(tmp10*Sy)))) - (4 * (tmp12*tmp128))) - (4 * (tmp11*tmp128))) - (4 * (tmp17*Sz))) + (4 * (tmp28*tmp127))) + (4 * (Dx*(tmp11*tmp127)))) + (4 * (Dx*(tmp10*tmp127)))) - (12 * (tmp12*tmp126))) - (4 * (tmp11*tmp126))) - (4 * (tmp10*tmp126))) - (8 * (Dx*(Dy*tmp125)))) - (8 * (Dx*(Dz*tmp124)))) - (4 * (tmp28*tmp123))) - (4 * (Dx*(tmp11*tmp123)))) - (4 * (Dx*(tmp10*tmp123)))) + (12 * (tmp12*tmp122))) + (4 * (tmp11*tmp122))) + (4 * (tmp10*tmp122))) + (8 * (Dx*(Dy*tmp121)))) + (8 * (Dx*(Dz*tmp120)))) - (12 * (tmp12*tmp119))) - (4 * (tmp11*tmp119))) - (4 * (tmp10*tmp119))) + (12 * (Dx*tmp118))) + (4 * (Dy*tmp117))) + (4 * (Dz*tmp116))) + (12 * (tmp12*tmp115))) + (4 * (tmp11*tmp115))) + (4 * (tmp10*tmp115))) - (12 * (Dx*tmp114))) - (4 * (Dy*tmp113))) - (4 * (Dz*tmp112))) + (12 * (Dx*(Ot*tmp27)))) - (4 * tmp111)) - (12 * (Dx*tmp110))) + (4 * tmp109)) - (4 * (Ot*tmp26))) + (4 * tmp108)) + (4 * (tmp12*(Dy*tmp107)))) + (4 * (tmp25*tmp107))) + (4 * (Dy*(tmp10*tmp107)))) - (8 * (Dx*(Dy*tmp106)))) - (4 * (tmp12*tmp105))) - (12 * (tmp11*tmp105))) - (4 * (tmp10*tmp105))) - (8 * (Dy*(Dz*tmp104)))) - (4 * (tmp12*(Dy*tmp103)))) - (4 * (tmp25*tmp103))) - (4 * (Dy*(tmp10*tmp103)))) + (8 * (Dx*(Dy*tmp102)))) + (4 * (tmp12*tmp101))) + (12 * (tmp11*tmp101))) + (4 * (tmp10*tmp101))) + (8 * (Dy*(Dz*tmp100)))) - (16 * (Dx*(Dy*(Ot*tmp24))))) + (8 * (Dy*tmp99))) + (8 * (Dx*tmp98))) + (16 * (Dx*(Dy*tmp97)))) - (8 * (Dy*tmp96))) - (8 * (Dx*tmp95))) + (12 * (Dy*(Ot*tmp23)))) - (4 * tmp94)) - (12 * (Dy*tmp93))) + (4 * tmp92)) - (4 * (tmp12*tmp91))) - (12 * (tmp11*tmp91))) - (4 * (tmp10*tmp91))) + (4 * (Dx*tmp90))) + (12 * (Dy*tmp89))) + (4 * (Dz*tmp88))) + (4 * (tmp12*tmp87))) + (12 * (tmp11*tmp87))) + (4 * (tmp10*tmp87))) - (4 * (Dx*tmp86))) - (12 * (Dy*tmp85))) - (4 * (Dz*tmp84))) + (12 * (Dx*(Ot*tmp22)))) - (4 * tmp83)) - (12 * (Dx*tmp82))) + (4 * tmp81)) - (8 * (Ot*tmp21))) + (8 * tmp80)) + (12 * (Dy*(Ot*tmp20)))) - (4 * tmp79)) - (12 * (Dy*tmp78))) + (4 * tmp77)) - (4 * (Ot*tmp19))) + (4 * tmp76)) + (4 * (tmp12*tmp75))) + (4 * (tmp11*tmp75))) + (4 * (tmp17*tmp74))) - (8 * (Dx*(Dz*tmp73)))) - (8 * (Dy*(Dz*tmp72)))) - (4 * (tmp12*tmp71))) - (4 * (tmp11*tmp71))) - (12 * (tmp10*tmp71))) - (4 * (tmp12*tmp70))) - (4 * (tmp11*tmp70))) - (4 * (tmp17*tmp69))) + (8 * (Dx*(Dz*tmp68)))) + (8 * (Dy*(Dz*tmp67)))) + (4 * (tmp12*tmp66))) + (4 * (tmp11*tmp66))) + (12 * (tmp10*tmp66))) - (16 * (Dx*(Dz*(Ot*tmp16))))) + (8 * (Dz*tmp65))) + (8 * (Dx*tmp64))) + (16 * (Dx*(Dz*tmp63)))) - (8 * (Dz*tmp62))) - (8 * (Dx*tmp61))) + (12 * (Dz*(Ot*tmp15)))) - (4 * tmp60)) - (12 * (Dz*tmp59))) + (4 * tmp58)) - (16 * (Dy*(Dz*(Ot*tmp14))))) + (8 * (Dz*tmp57))) + (8 * (Dy*tmp56))) + (16 * (Dy*(Dz*tmp55)))) - (8 * (Dz*tmp54))) - (8 * (Dy*tmp53))) + (12 * (Dz*(Ot*tmp13)))) - (4 * tmp52)) - (12 * (Dz*tmp51))) + (4 * tmp50)) - (4 * (tmp12*tmp49))) - (4 * (tmp11*tmp49))) - (12 * (tmp10*tmp49))) + (4 * (Dx*tmp48))) + (4 * (Dy*tmp47))) + (12 * (Dz*tmp46))) + (4 * (tmp12*tmp45))) + (4 * (tmp11*tmp45))) + (12 * (tmp10*tmp45))) - (4 * (Dx*tmp44))) - (4 * (Dy*tmp43))) - (12 * (Dz*tmp42))) + (12 * (Dx*(Ot*tmp9)))) - (4 * tmp41)) - (12 * (Dx*tmp40))) + (4 * tmp39)) - (8 * (Ot*tmp7))) + (8 * tmp38)) + (12 * (Dy*(Ot*tmp6)))) - (4 * tmp37)) - (12 * (Dy*tmp36))) + (4 * tmp35)) - (8 * (Ot*tmp3))) + (8 * tmp34)) + (12 * (Dz*(Ot*tmp2)))) - (4 * tmp33)) - (12 * (Dz*tmp32))) + (4 * tmp31)) - (4 * (Ot*tmp1))) + (4 * tmp30));
		const double a = (((((((((((((((((((((((((((((((((((((((((Power(Dx, 4) + (2 * (tmp12*tmp11))) + Power(Dy, 4)) + (2 * (tmp12*tmp10))) + (2 * (tmp11*tmp10))) + Power(Dz, 4)) - (4 * (tmp28*Vx))) - (4 * (Dx*(tmp11*Vx)))) - (4 * (Dx*(tmp10*Vx)))) + (6 * (tmp12*tmp8))) + (2 * (tmp11*tmp8))) + (2 * (tmp10*tmp8))) - (4 * (Dx*tmp27))) + tmp26) - (4 * (tmp12*(Dy*Vy)))) - (4 * (tmp25*Vy))) - (4 * (Dy*(tmp10*Vy)))) + (8 * (Dx*(Dy*tmp24)))) - (4 * (Dy*tmp23))) + (2 * (tmp12*tmp5))) + (6 * (tmp11*tmp5))) + (2 * (tmp10*tmp5))) - (4 * (Dx*tmp22))) + (2 * tmp21)) - (4 * (Dy*tmp20))) + tmp19) - (4 * (tmp12*tmp18))) - (4 * (tmp11*tmp18))) - (4 * (tmp17*Vz))) + (8 * (Dx*(Dz*tmp16)))) - (4 * (Dz*tmp15))) + (8 * (Dy*(Dz*tmp14)))) - (4 * (Dz*tmp13))) + (2 * (tmp12*tmp4))) + (2 * (tmp11*tmp4))) + (6 * (tmp10*tmp4))) - (4 * (Dx*tmp9))) + (2 * tmp7)) - (4 * (Dy*tmp6))) + (2 * tmp3)) - (4 * (Dz*tmp2))) + tmp1);
#endif

		slns = SolveQuartic(a, b, c, d, e);
	}

	IntersectionList lst;

	Intersection isect;
	isect.Colour = Colour;
	isect.IncomingDir = ray.Direction;
	isect.SurfaceVel = Vector3d::zero();
	isect.Object = this;
	isect.RefFrame = RefFrame;

	for (auto dist : slns)
	{
		isect.Position = ray.Origin + Vector4d(ray.GetFourVelocity() * dist);
		auto relpos = isect.Position.xyz() - (InitialPosition.xyz() + RefFrame.Velocity * InitialPosition.t);
		auto a = 1 - (Radius / std::sqrt(relpos.x * relpos.x + relpos.y * relpos.y));
		isect.Normal = normalize(Vector3d(relpos.xy() * a, relpos.z));
	}

	return lst;
}