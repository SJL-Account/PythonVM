
var_a = 1
var_b = 0
var_i = 1

print var_a
print var_b

while var_i < 10:
    var_t = var_a
    var_a = var_a + var_b
    var_b = var_t
    var_i = var_i + 1

print var_a