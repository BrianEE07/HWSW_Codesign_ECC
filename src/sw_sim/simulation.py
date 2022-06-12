# from statistics import multimode
# from ecc_binary_field.binop import *
import numpy as np
# def poly_mod(x1,bitnum, poly = '100011101'):
#     x1_b = bin(x1)
#     temp = int(mod(x1_b,poly),2)
#     return temp

# def multiple_sofeware(x1, x2, bitnum):
#     temp1_b_inv = format(x1,"b")
#     temp2_b_inv = format(x2,"b")
#     temp1_b = temp1_b_inv[::-1]
#     temp2_b = temp2_b_inv[::-1]
#     temp1_len = len(temp1_b)
#     temp2_len = len(temp2_b)
#     ans = 0
#     for i in range(temp1_len):
#         if(temp1_b[i] == "1") : 
#             for j in range(temp2_len) :
#                 if(temp2_b[j] == "1"):
#                     power = (i+j) % 15
#                     lutt = LUT(power, bitnum)
#                     ans = addition(ans, lutt)
#     return ans 

def addition(x1, x2):
    temp = x1 ^ x2
    return temp

def square(x1, bitnum, k):  # put 0 into temp, no need to reverse string
    temp = format(x1,"b")  
    if(len(temp) != bitnum):
        for i in range(bitnum-len(temp)):
            temp = "0" + temp
    temp_ans_li = []
    for i in range(bitnum):
        temp_ans_li.append(temp[i])
        if i != bitnum -1: 
            temp_ans_li.append("0")
    temp_ans = "".join(temp_ans_li)
    ans = int(temp_ans, 2)
    # ans = poly_mod(ans, bitnum)  # mod f(x)
    ans = poly_mod_hardware(ans,bitnum, k)
    return ans

def inverse_Itoh(x1,bitnum,k):
    a = x1
    if bitnum == 167:
        u = [1, 2, 3, 5, 10, 20, 40, 80, 83, 166]
        v = [(None,None), (0,0), (1,0), (2,1), (3,3), (4,4), (5,5), (6,6), (7,2), (8,8)]
        betas = [a] ## betas[0] = a
        for i in range(1,10): ## i1 = v[i][0], i2 = v[i][1]
            i1, i2 = v[i][0], v[i][1]
            temp1 = betas[i1]
            temp2 = betas[i2]
            for j in  range( u[i2] ):
                temp1 = square(temp1,bitnum,k)
            beta_i = multiple_hardware(temp1, temp2, bitnum, k)
            betas.append(beta_i)
        out = square(betas[9], bitnum, k)
        out = np.binary_repr(out)
        return int(out,2)

    elif bitnum == 163:
        u = [1, 2, 4, 8, 16, 32, 64, 80, 81]
        v = [(None,None), (0,0), (1,1), (2,2), (3,3), (4,4), (5,5), (6,4), (7,0), (8,8)]
        betas = [a] ## betas[0] = a
        for i in range(1,10): ## i1 = v[i][0], i2 = v[i][1]
            i1, i2 = v[i][0], v[i][1]
            temp1 = betas[i1]
            temp2 = betas[i2]
            for j in  range( u[i2] ):
                temp1 = square(temp1,bitnum,k)
            beta_i = multiple_hardware(temp1, temp2, bitnum, k)
            betas.append(beta_i)
        out = square(betas[9], bitnum, k)
        out = np.binary_repr(out)
        return int(out,2)
    raise "inverse_Itoh"

def poly_mod_hardware(x1, bitnum, k, specific = 0):    # specific for m = 167, k = 6   #specific  == 1 failed 
    x1_b_rebpol = format(x1,"b")
    x1_b = x1_b_rebpol[::-1]
    if(len(x1_b)!= 2*bitnum):
        for i in range(2*bitnum - len(x1_b)):
            x1_b = x1_b + "0"
    if bitnum == 163: #Karatsuba
        temp_list = []
        for i in range(bitnum):
            if i <= 1 : 
                temp1 = int(x1_b[i],2)
                temp2 = int(x1_b[i+163],2)
                temp3 = int(x1_b[i+319],2)
                temp4 = int(x1_b[i+320],2)
                temp5 = int(x1_b[i+323],2)
                bit_ans = temp1 ^ temp2 ^ temp3 ^ temp4 ^ temp5
                temp_list.append(str(bit_ans))
            elif i == 2: 
                temp1 = int(x1_b[2],2)
                temp2 = int(x1_b[165],2)
                temp3 = int(x1_b[321],2)
                temp4 = int(x1_b[322],2)
                bit_ans = temp1 ^ temp2 ^ temp3 ^ temp4 
                temp_list.append(str(bit_ans))
            elif i <= 5: 
                temp1 = int(x1_b[i],2)
                temp2 = int(x1_b[i+163],2)
                temp3 = int(x1_b[i+160],2)
                temp4 = int(x1_b[i+319],2)
                temp5 = int(x1_b[i+316],2)
                temp6 = int(x1_b[i+317],2)
                bit_ans = temp1 ^ temp2 ^ temp3 ^ temp4 ^ temp5 ^ temp6
                temp_list.append(str(bit_ans))
            elif i == 6:
                temp1 = int(x1_b[6],2)
                temp2 = int(x1_b[169],2)
                temp3 = int(x1_b[163],2)
                temp4 = int(x1_b[166],2)
                temp5 = int(x1_b[322],2)
                temp6 = int(x1_b[319],2)
                temp7 = int(x1_b[320],2)
                bit_ans = temp1 ^ temp2 ^ temp3 ^ temp4 ^ temp5 ^ temp6 ^ temp7
                temp_list.append(str(bit_ans))
            elif i <= 10: 
                temp1 = int(x1_b[i],2)
                temp2 = int(x1_b[i+163],2)
                temp3 = int(x1_b[i+156],2)
                temp4 = int(x1_b[i+157],2)
                temp5 = int(x1_b[i+160],2)
                temp6 = int(x1_b[i+312],2)
                temp7 = int(x1_b[i+314],2)
                bit_ans = temp1 ^ temp2 ^ temp3 ^ temp4 ^ temp5 ^ temp6 ^ temp7
                temp_list.append(str(bit_ans))
            elif i <= 12:
                temp1 = int(x1_b[i],2)
                temp2 = int(x1_b[i+163],2)
                temp3 = int(x1_b[i+156],2)
                temp4 = int(x1_b[i+157],2)
                temp5 = int(x1_b[i+160],2)
                temp6 = int(x1_b[i+312],2)
                bit_ans = temp1 ^ temp2 ^ temp3 ^ temp4 ^ temp5 ^ temp6
                temp_list.append(str(bit_ans))
            elif i<= 161:
                temp1 = int(x1_b[i],2)
                temp2 = int(x1_b[i+163],2)
                temp3 = int(x1_b[i+156],2)
                temp4 = int(x1_b[i+157],2)
                temp5 = int(x1_b[i+160],2)
                bit_ans = temp1 ^ temp2 ^ temp3 ^ temp4 ^ temp5
                temp_list.append(str(bit_ans))
            else :
                temp1 = int(x1_b[162],2)
                temp2 = int(x1_b[318],2)
                temp3 = int(x1_b[319],2)
                temp4 = int(x1_b[322],2)
                bit_ans = temp1 ^ temp2 ^ temp3 ^ temp4
                temp_list.append(str(bit_ans))
        ans_inv = "".join(temp_list)
        ans = int(ans_inv[::-1],2)
    elif k == 1: 
        raise
        temp_list = []
        for i in range(bitnum):
            if i == 0 : 
                temp = str(int(x1_b[0],2) ^ int(x1_b[bitnum],2))
                temp_list.append(temp)
            elif i <= bitnum - 2 :
                temp = str((int(x1_b[i],2) ^ int(x1_b[bitnum + i - 1],2) )^ int(x1_b[bitnum + i],2))
                temp_list.append(temp)
            else : 
                temp = str(int(x1_b[bitnum-1],2) ^ int(x1_b[2*bitnum-2],2))
                temp_list.append(temp)
        ans_inv = "".join(temp_list)
        ans = int(ans_inv[::-1],2)
    elif k == 6 and specific == 1: # don't use this shit
        temp_list = []
        for i in range(bitnum):
            if i <= 4 : 
                si = int(x1_b[i],2)
                si_167 = int(x1_b[i+167],2)
                si_328 = int(x1_b[i+328],2)
                bit_ans = si ^ si_167 ^ si_328
                temp = str(bit_ans)
                temp_list.append(temp)
            elif i == 5 : 
                s5 = int(x1_b[5],2)
                s_172 = int(x1_b[172],2)
                bit_ans = s5 ^ s_172
                temp = str(bit_ans)
                temp_list.append(temp)
            elif i <= 10 : 
                si = int(x1_b[i],2)
                si_167 = int(x1_b[i+167],2)
                bit_ans = si ^ si_167 
                temp = str(bit_ans)
                temp_list.append(temp)
            elif i <= 165 : 
                si = int(x1_b[i],2)
                si_167 = int(x1_b[i+167],2)
                si_161 = int(x1_b[i+161],2)
                bit_ans = si ^ si_167 ^ si_161
                temp = str(bit_ans)
                temp_list.append(temp)                
            else:
                s_166 = int(x1_b[166],2)
                s_327 = int(x1_b[327],2)
                bit_ans = s_166 ^ s_327
                temp = str(bit_ans)
                temp_list.append(temp)   
        ans_inv = "".join(temp_list)
        ans = int(ans_inv[::-1],2)
    elif k == 6 and specific == 0 : 
        temp_list = []
        for i in range(bitnum):
            if i <= k-2:
                si = int(x1_b[i],2)
                si_m = int(x1_b[i+bitnum],2)
                si_2m_minus_k = int(x1_b[2*bitnum+i-k],2)
                bit_ans = si ^ si_m ^ si_2m_minus_k
                temp = str(bit_ans)
                temp_list.append(temp)
            elif i == k-1 : 
                sk_minus_1 = int(x1_b[k-1],2)
                sk_m_minus_1 = int(x1_b[bitnum+k-1],2)
                bit_ans = sk_minus_1 ^ sk_m_minus_1
                temp = str(bit_ans)
                temp_list.append(temp)                
            elif i <= (2*k)-2:
                si = int(x1_b[i],2)
                si_m = int(x1_b[i+bitnum],2)
                si_m_minus_k = int(x1_b[i+bitnum-k],2)
                si_2m_minus_2k = int(x1_b[i+2*bitnum-2*k],2)
                bit_ans=  si ^ si_m ^ si_2m_minus_2k ^ si_m_minus_k
                temp = str(bit_ans)
                temp_list.append(temp)
            elif i <= bitnum-2:
                si = int(x1_b[i],2)
                si_m = int(x1_b[i+bitnum],2)
                si_m_minus_k = int(x1_b[i+bitnum-k],2)
                bit_ans = si ^ si_m ^ si_m_minus_k
                temp = str(bit_ans)
                temp_list.append(temp)
            else :
                sm_minus_1 = int(x1_b[bitnum-1],2)
                s2m_minusk_minus1 = int(x1_b[2*bitnum - k - 1],2)
                bit_ans = sm_minus_1 ^ s2m_minusk_minus1
                temp = str(bit_ans)
                temp_list.append(temp)
        ans_inv = "".join(temp_list)
        ans = int(ans_inv[::-1],2)
    else : raise
    return ans

def multiple_hardware(x1, x2, bitnum, k) : 
    if bitnum == 163: ## Karatsuba Multiplier
        x1 = format(x1,"b") #[h -> l]
        x2 = format(x2,"b") #[h -> l]
        if(len(x1)!= bitnum):
            for i in range(bitnum - len(x1)):
                x1 = "0" + x1
        if(len(x2)!= bitnum):
            for i in range(bitnum - len(x2)):
                x2 = "0" + x2
        x1_h, x1_l = x1[ 0: 82], x1[82:163] #[h -> l] ## 82, 81
        x2_h, x2_l = x2[ 0: 82], x2[82:163] #[h -> l]  ## 82, 81
        mid1, mid2 = addition( int(x1_l,2), int(x1_h,2) ), addition( int(x2_l,2), int(x2_h,2) )
        mid1, mid2 = format(mid1,"b"), format(mid2,"b")  #[h -> l]
        x2_l, x2_h, mid2 = int(x2_l,2), int(x2_h,2), int(mid2,2)
        ## compute low1 * low2 = ll
        x1_l = x1_l[::-1]
        ll = 0
        if(len(x1_l)!= 2*bitnum):
            for i in range(2*bitnum - len(x1_l)):
                x1_l = x1_l + "0"
        for i in range(2*bitnum):
            if x1_l[i] == "1" : 
                ll = ll ^ x2_l
            else : 
                ll = ll 
            x2_l = x2_l << 1        
        ## compute high1 * high2 = hh
        x1_h = x1_h[::-1]
        hh = 0
        if(len(x1_h)!= 2*bitnum):
            for i in range(2*bitnum - len(x1_h)):
                x1_h = x1_h + "0"
        for i in range(2*bitnum):
            if x1_h[i] == "1" : 
                hh = hh ^ x2_h
            else : 
                hh = hh 
            x2_h = x2_h << 1 
        #hh = poly_mod_hardware(hh, bitnum, k)
        ## compute mid = (x1_l + x1_h) * (x2_l + x2_H) = mm
        mid1 = mid1[::-1]
        mm = 0
        if(len(mid1)!= 2*bitnum):
            for i in range(2*bitnum - len(mid1)):
                mid1 = mid1 + "0"
        for i in range(2*bitnum):
            if mid1[i] == "1" : 
                mm = mm ^ mid2
            else : 
                mm = mm 
            mid2 = mid2 << 1 
        mm = addition(mm,ll)
        mm = addition(mm,hh)
        #mm = poly_mod_hardware(mm, bitnum, k)
        ##  ans = (ll << 162) + (mm << 81) + hh
        ans = addition( (mm <<  81) ,  ll)
        ans = addition( (hh << 162) , ans)
        ans = poly_mod_hardware(ans, bitnum, k)
        return ans
    temp1_b_inv = format(x1,"b")
    temp1_b = temp1_b_inv[::-1]
    ans = 0
    if(len(temp1_b)!= 2*bitnum):
        for i in range(2*bitnum - len(temp1_b)):
            temp1_b = temp1_b + "0"
    for i in range(2*bitnum):
        if temp1_b[i] == "1" : 
            ans = ans ^ x2
        else : 
            ans = ans 
        x2 = x2 << 1 
    #print(f'multiple {x1} * {x2}, answer before mod is {ans}')
    ans = poly_mod_hardware(ans, bitnum, k)
    return ans

# def examine(x,y,a,b,bitnum, k): # don't use this shit
#     # y^2 + xy = x^3 + ax^2 + b, a, b != 0
#     if(x == -1) :
#         # print("examining x = -1")
#         return 1
#     elif x == 0 and y == 0 :
#         return 0
#     x2 = square(x, bitnum,k)
#     x3  = multiple_hardware(x, x2, bitnum, k)
#     ax2 = multiple_hardware(a, x2, bitnum, k)
#     delta = addition(ax2,b) 
#     delta = addition(x3, delta) 
#     xy = multiple_hardware(x, y, bitnum, k)
#     y2 = multiple_hardware(y, y, bitnum, k)
#     left = addition(y2, xy) 
#     if delta-left == 0 : return 1
#     else : return 0

def point_negation(x1, y1, bitnum):
    x_o = x1
    y_o = addition(x1,y1)
    return x_o, y_o

def point_doubling(x1, y1, bitnum, a, k) :
    # calculating x_o
    x1_neg ,y1_neg = point_negation(x1,y1,bitnum)
    if x1 == x1_neg and y1 == y1_neg : 
        # print("point doubling and P = -P")
        # raise
        return -1 ,0
    elif x1 == -1 : return -1,0
    #x1_inv_mul_y1 = int(divide(bin(y1), bin(x1),polynomial),2)
    temp1 = inverse_Itoh(x1,bitnum,k)
    x1_inv_mul_y1 = multiple_hardware(y1, temp1, bitnum, k)
    lamb = addition(x1, x1_inv_mul_y1)
    if lamb == -1 : 
        # print("fuck here")
        raise
    lamb_2 = square(lamb, bitnum,k)
    x_o = addition(addition(lamb_2, lamb), a)
    # calculating y_o
    x1_2 = square(x1, bitnum,k)
    if(x1 ==0) :
        # print("fuck here 2 ")
        raise
    # lamb_mul_x_o = multiple_sofeware(lamb, x_o, bitnum)
    lamb_mul_x_o = multiple_hardware(lamb, x_o, bitnum,k)
    y_o = addition(addition(x1_2,lamb_mul_x_o), x_o)
    return x_o, y_o

def point_addition(x1, y1, x2, y2, bitnum, a,k) :
    # calculating x_o
    # suppose O = -1, 0
    x2_n, y2_n = point_negation(x2,y2,bitnum)
    if x1 != x2 or y1 != y2 :
        if x1 == x2_n and y1 == y2_n : return -1,0
        elif x1 == -1 : return x2, y2
        elif x2 == -1 : return x1, y1
        y2_add_y1 = addition(y2, y1) 
        x2_add_x1 = addition(x2, x1)
        #lamb = int(divide(bin(y2_add_y1),bin(x2_add_x1),polynomial),2)
        #lamb_0 = int(inverse(bin(x2_add_x1),polynomial),2)
        lamb_0 = inverse_Itoh(x2_add_x1,bitnum,k)
        lamb = multiple_hardware(y2_add_y1, lamb_0, bitnum, k)
        lamb_2 = square(lamb, bitnum,k)
        x_o = addition(addition(addition(lamb, lamb_2), addition(x1,x2)), a)
        # calculation y_o
        x1_add_x_o = addition(x1, x_o)
        lamb_mul_x1_add_xo = multiple_hardware(lamb, x1_add_x_o, bitnum, k)
        y_o = addition(addition(lamb_mul_x1_add_xo, x_o), y1)
        return x_o, y_o
    else : 
        x_o, y_o = point_doubling(x1,y1, bitnum, a,k)
        return x_o, y_o

def scalar_multiple(k, x1, y1, bitnum, a,k_poly):
    a_x = x1
    a_y = y1
    r_x = -1
    r_y = 0
    while k > 0 :
        if k%2 == 1 :
            temp_r_x , temp_r_y = r_x, r_y
            r_x, r_y = point_addition(temp_r_x, temp_r_y, a_x, a_y, bitnum, a,k_poly)
        k = k >> 1
        temp_a_x , temp_a_y = a_x, a_y
        a_x, a_y = point_doubling(temp_a_x, temp_a_y, bitnum, a,k_poly)
    return r_x, r_y

def scalar_multiple_projective(k, x1, y1, bitnum, b,k_poly, to_print=0):
    xp = x1
    yp = y1
    K = bin(k)[3:]
    n = len(K) # from k_n-2 to k_0, 
    ## used intermediated term
    T1, T2, T3 = 0, 0, 0
    Z1, Z2     = 0, 0
    X1, X2     = 0, 0
    ## Affine to Projective
    Z2 = square(xp, bitnum, k_poly)  ## xp^2
    if( to_print == 1):
        print(f'Z2 = {hex(Z2)}\n')
    X1 = xp
    if( to_print == 1):
        print(f'X1 = {hex(X1)}\n') 
    X2 = square(Z2, bitnum, k_poly)
    if( to_print == 1):
        print(f'X2 = {hex(X2)}\n') 
    Z1 = 1
    if( to_print == 1):
        print(f'Z1 = {hex(Z1)}\n') 
    if( to_print == 1):
        print(f'X2 : {hex(addition(X2,b) )} = reg1 : {hex(b)} + reg2 : {hex(X2)} \n') 
    X2 = addition(X2,b)              ## X2 = xp^4 +b

    if( to_print == 1):
        print("a->f") 
        print(f'X1 = {hex(X1)}\n') 
        print(f'X2 = {hex(X2)}\n') 
        print(f'Z1 = {hex(Z1)}\n') 
        print(f'Z2 = {hex(Z2)}\n') 
        print(f'K = {K}\n')

    ## Scalar Multiplication Loop Process

    for i in range(n): ## i = n-2 to 0
        if (K[i] == '1'):   
            Z1 = multiple_hardware(X2, Z1, bitnum, k_poly)
            if( to_print == 1 and i == 0 ):
                print("first mul") 
                print(f'Z1 = {hex(Z1)}\n') 
            X1 = multiple_hardware(X1, Z2, bitnum, k_poly)
            if( to_print == 1 and i == 0 ):
                print("second mul") 
                print(f'X1 = {hex(X1)}\n') 
            T1 = addition(X1, Z1)
            if( to_print == 1 and i == 0 ):
                print("add") 
                print(f'T1= {hex(T1)}\n') 
            X1 = multiple_hardware(X1, Z1, bitnum, k_poly)
            Z1 = square(T1, bitnum, k_poly)
            T1 = multiple_hardware(xp, Z1, bitnum, k_poly)
            X1 = addition(X1, T1)
            # P = 2P for k_i == 1 
            Z2 = square(Z2, bitnum, k_poly)
            T1 = square(Z2, bitnum, k_poly)
            T1 = multiple_hardware( b, T1, bitnum, k_poly)
            X2 = square(X2, bitnum, k_poly)
            Z2 = multiple_hardware(X2, Z2, bitnum, k_poly)
            X2 = square(X2, bitnum, k_poly)
            X2 = addition(X2, T1)
        else:
            # P = P + Q for k_i == 0
            Z2 = multiple_hardware(X1, Z2, bitnum, k_poly)
            X2 = multiple_hardware(X2, Z1, bitnum, k_poly)
            if( to_print == 1):
                print("start of debug")
                print(f'X2 = {hex(X2)}\n')
                print(f'Z2 = {hex(Z2)}\n')
            T1 = addition(X2, Z2)
            X2 = multiple_hardware(X2, Z2, bitnum, k_poly)
            Z2 = square(T1, bitnum, k_poly)
            if( to_print == 1):
                print(f'T1 = {hex(T1)}\n')
                print(f'Z2 = {hex(Z2)}\n')
            T1 = multiple_hardware(xp, Z2, bitnum, k_poly)
            X2 = addition(X2, T1)
            # P = 2P for k_i == 0
            Z1 = square(Z1, bitnum, k_poly)
            T1 = square(Z1, bitnum, k_poly)
            T1 = multiple_hardware(b, T1, bitnum, k_poly)
            X1 = square(X1, bitnum, k_poly)
            Z1 = multiple_hardware(X1, Z1, bitnum, k_poly)
            X1 = square(X1, bitnum, k_poly)
            X1 = addition(X1, T1)
    ## Projective to Affine 
    if( to_print == 1):
        print(f'Z1 = {hex(Z1)}\n')
        print(f'Z2 = {hex(Z2)}\n')
        print(f'T4 = {hex(multiple_hardware(Z1, Z2, bitnum, k_poly))}\n')
    T4 = multiple_hardware(Z1, Z2, bitnum, k_poly)
    T1 = multiple_hardware(xp, T4, bitnum, k_poly)
    T2 = inverse_Itoh(T1,bitnum,k_poly)
    T1 = multiple_hardware(xp, Z1, bitnum, k_poly)
    T3 = multiple_hardware(xp, Z2, bitnum, k_poly)
    T1 = addition(X1,T1)
    T3 = addition(X2,T3)
    T1 = multiple_hardware(T1, T3, bitnum, k_poly)
    T3 = square(xp, bitnum, k_poly)
    T3 = addition(yp,T3)
    T3 = multiple_hardware(T3, T4, bitnum, k_poly)
    T1 = addition(T1,T3)
    T1 = multiple_hardware(T1, T2, bitnum, k_poly)
    T2 = inverse_Itoh(Z1,bitnum,k_poly)
    T2 = multiple_hardware(X1, T2, bitnum, k_poly)
    # print 
    if( to_print == 1):
        print(f'T2 = {hex(T2)}\n')
    T3 = addition(xp,T2)
    if( to_print == 1):
        print(f'T3 = {hex(T3)}\n')
    T1 = multiple_hardware(T1, T3, bitnum, k_poly)
    if( to_print == 1):
        print(f'T1 = {hex(T1)}\n')
    T1 = addition(yp,T1)
    if( to_print == 1):
        print(f'T1 = {hex(T1)}\n')
    return T2, T1

# def print_all_point(bitnum,a,b) : 
#     for x in range(2**bitnum):
#         for y in range(2**bitnum):
#             if examine(x,y,a,b,bitnum):
#                 print(f"x:,{x:.3f}, y:{y:.3f}")

if __name__ == "__main__" :

    print("Start simulation !! ")
    # # this is for ECC-167 ----------------------
    # Px ,Py = int('0x2_FE13_C053_7BBC_11AC_AA07_D793_DE4E_6D5E_5C94_EEE8',16), int('0x2_8907_0FB0_5D38_FF58_321F_2E80_0536_D538_CCDA_A3D9',16)
    # bitnum = 167
    # polynomial = str()
    # for i in range(bitnum+1): 
    #     if i == 0 or i == 6 or i == bitnum : # x^167 + x^6 + 1
    #         polynomial = "1" + polynomial 
    #     else : 
    #         polynomial = "0" + polynomial
    # k_in_polynomial = 6
    # a , b = 1,1

    # this is for ECC-163 ------------------------
    bitnum = 163
    polynomial = str()
    for i in range(bitnum+1): 
        if i == 0 or i == 3 or i == 6 or i == 7 or i == bitnum : # x^163 + x^7 + x^6 + x^3 + 1
            polynomial = "1" + polynomial 
        else : 
            polynomial = "0" + polynomial
    # polynimial = 多項式的係數
    Px ,Py = int('0x3_f0eba162_86a2d57e_a0991168_d4994637_e8343e36',16) , int('0xd51fbc6c_71a0094f_a2cdd545_b11c5c0c_797324f1',16)
    k_in_polynomial = 1234
    a , b = 1 , int('0x2_0a601907_b8c953ca_1481eb10_512f7874_4a3205fd',16)
    k1 , k2 = 6 , 10 # 150 bit 
    # inverse_table = inverse_table_generator(bitnum,k_in_polynomial)
    inverse_table = []
    # y^2 + xy = x^3 + ax^2 + b, a, b != 0
    # Uncomment to print all point
    # print_all_point(bitnum,a,b)
    # Set arguments
    # ## Affine
    x1, y1 = scalar_multiple(k1, Px, Py, bitnum, a, k_in_polynomial)
    ans_x_1, ans_y_1 = scalar_multiple(k2, x1, y1, bitnum, a, k_in_polynomial)
    x2, y2 = scalar_multiple(k2, Px, Py, bitnum, a, k_in_polynomial)
    ans_x_2, ans_y_2 = scalar_multiple(k1, x2, y2, bitnum, a, k_in_polynomial)
    k3 = k1 * k2
    x3, y3 = scalar_multiple(k3,Px,Py,bitnum,a, k_in_polynomial)
    ## Projective 
    # x1, y1 = scalar_multiple_projective(k1, Px, Py, bitnum, b, k_in_polynomial, to_print=1)
    # ans_x_1, ans_y_1 = scalar_multiple_projective(k2, x1, y1, bitnum, b, k_in_polynomial)
    # x2, y2 = scalar_multiple_projective(k2, Px, Py, bitnum, b, k_in_polynomial)
    # ans_x_2, ans_y_2 = scalar_multiple_projective(k1, x2, y2, bitnum, b, k_in_polynomial)
    # k3 = k1 * k2
    # x3, y3 = scalar_multiple_projective(k3,Px,Py,bitnum,b,  k_in_polynomial)
    print(f'Selected Elliptical Curve Equation In GF(2^m): y^3 + xy = x^3 + {a}x^2 + {b}\n')
    print(f'Start point P(x,y) = ( {Px} , {Py} )\n')
    print(f'Assume Bob   choose {k1} and send k1*P to Alice\n')
    print(f'Assume Alice choose {k2} and send k2*P to Bob\n')
    print(f'Bob received k2*P and apply k1*(k2*P), and Alice received k1*P and apply k2*(k1*P)\n')
    if ans_x_1 == ans_x_2 and ans_y_1 == ans_y_2 and ans_x_1 == x3 and ans_y_1 == y3: 
        print("simulation result : success")
        print(f'k1(k2*P) = k2*(k1*P) ({ans_x_1}, {ans_y_1})')
        print("")
        print(f'k1*P ({x1},{y1})')
        print(f'k2*P ({x2},{y2})')
    else : 
        print(f'k2(k1*P) = {ans_x_1}, {ans_y_1}')
        print(f'k1(k2*P) = {ans_x_2}, {ans_y_2}')
        print("main fucked")
        if (ans_x_1 == ans_x_2): print("but k2(k1*P).x= k1(k2*P).x")
        raise

    data_a = int('0x58efc9fddedc2cccccdd230ff201392ffcfdaaa',16)
    data_b = int('0x6904f23090276756cd402982eff1cdc24449204',16)
    ansss = multiple_hardware(data_a, data_b, 163, 111)

    print(f' ansss = {ansss}')


''' 
poly_mod_hardware
addition
square
    poly_mod_hardware
inverse_Itoh
    square
    multiple_hardware
multiple_hardware
    addition
    poly_mod_hardware
point_negation
    addition
point_doubling
    point_negation
    inverse_Itoh
    multiple_hardware
    addition
    square
point_addition
    point_negation
    addition
    inverse_Itoh
    multiple_hardware
    square
    point_doubling
scalar_multiple
    point_addition
    point_doubling
scalar_multiple_projective
    square
    addition
    multiple_hardware
    inverse_Itoh
'''