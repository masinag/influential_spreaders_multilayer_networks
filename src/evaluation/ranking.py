# import math

# EPS = 1e-06

# def sign(x):
#     return 0 if math.isclose(x, 0, rel_tol=EPS) else 1 if x > 0 else -1

# def kendallsTau(x, y):
#     count = 0
#     for i in range(1, len(x)):
#         for j in range(i):
#             count += sign(x[i] - x[j]) * sign(y[i] - y[j])
#     return 2 * count / (len(x) * (len(x) - 1))

# def kendallsTauB(x, y):
#      P = 0
#      Q = 0
#      T = 0
#      U = 0
#      for i in range(1, len(x)):
#              for j in range(i):
#                      s1 = x[i] - x[j]
#                      s2 = y[i] - y[j]
#                      if not (s1 == 0 and s2 == 0):
#                         if s1 == 0 and s2 != 0:
#                                 T += 1
#                         elif s1 != 0 and s2 == 0:
#                                 U += 1
#                         elif s1 * s2 > 0:
#                                 P += 1
#                         else:
#                                 Q += 1
#      return (P - Q) / math.sqrt((P + Q + T) * (P + Q + U))
