import numpy as np



if __name__ == "__main__":
    print("Start Simulation !!")
    # for ECC-163 (GF(2^163))
    bitnum = 163
    Px ,Py = int('0x3_f0eba162_86a2d57e_a0991168_d4994637_e8343e36',16), int('0xd51fbc6c_71a0094f_a2cdd545_b11c5c0c_797324f1',16)
    k_in_polynomial = 1234
    a , b = 1 , int('0x2_0a601907_b8c953ca_1481eb10_512f7874_4a3205fd',16)
    k1 , k2 = 6 , 10 # 150 bit 
    print(format(Py, "b"))
    # inverse_table = inverse_table_generator(bitnum,k_in_polynomial)
    # inverse_table = []
    # y^2 + xy = x^3 + ax^2 + b, a, b != 0
    # Uncomment to print all point
    # print_all_point(bitnum,a,b)
    # Set arguments
    # ## Affine
    # x1, y1 = scalar_multiple(k1, Px, Py, bitnum, a, k_in_polynomial)
    # ans_x_1, ans_y_1 = scalar_multiple(k2, x1, y1, bitnum, a, k_in_polynomial)
    # x2, y2 = scalar_multiple(k2, Px, Py, bitnum, a, k_in_polynomial)
    # ans_x_2, ans_y_2 = scalar_multiple(k1, x2, y2, bitnum, a, k_in_polynomial)
    # k3 = k1 * k2
    # x3, y3 = scalar_multiple(k3,Px,Py,bitnum,a, k_in_polynomial)
    ## Projective 
    # x1, y1 = scalar_multiple_projective(k1, Px, Py, bitnum, b, k_in_polynomial, to_print=1)
    # ans_x_1, ans_y_1 = scalar_multiple_projective(k2, x1, y1, bitnum, b, k_in_polynomial)
    # x2, y2 = scalar_multiple_projective(k2, Px, Py, bitnum, b, k_in_polynomial)
    # ans_x_2, ans_y_2 = scalar_multiple_projective(k1, x2, y2, bitnum, b, k_in_polynomial)
    # k3 = k1 * k2
    # x3, y3 = scalar_multiple_projective(k3,Px,Py,bitnum,b,  k_in_polynomial)
    # print(f'Selected Elliptical Curve Equation In GF(2^m): y^2 + xy = x^3 + {a}x^2 + {b}\n')
    # print(f'Start point P(x,y) = ( {Px} , {Py} )\n')
    # print(f'Assume Bob   choose {k1} and send k1*P to Alice\n')
    # print(f'Assume Alice choose {k2} and send k2*P to Bob\n')
    # print(f'Bob received k2*P and apply k1*(k2*P), and Alice received k1*P and apply k2*(k1*P)\n')
    # if ans_x_1 == ans_x_2 and ans_y_1 == ans_y_2 and ans_x_1 == x3 and ans_y_1 == y3: 
    #     print("simulation result : success")
    #     print(f'k1(k2*P) = k2*(k1*P) ({ans_x_1}, {ans_y_1})')
    #     print("")
    #     print(f'k1*P ({x1},{y1})')
    #     print(f'k2*P ({x2},{y2})')
    # else : 
    #     print(f'k2(k1*P) = {ans_x_1}, {ans_y_1}')
    #     print(f'k1(k2*P) = {ans_x_2}, {ans_y_2}')
    #     print("main fucked")
    #     if (ans_x_1 == ans_x_2): print("but k2(k1*P).x= k1(k2*P).x")
    #     raise

    # data_a = int('0x58efc9fddedc2cccccdd230ff201392ffcfdaaa',16)
    # data_b = int('0x6904f23090276756cd402982eff1cdc24449204',16)
    # ansss = multiple_hardware(data_a, data_b, 163, 111)

    # print(f' ansss = {ansss}')
