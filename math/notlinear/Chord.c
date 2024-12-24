double chord_method(double x0, double x1, double tolerance) {
    double x2;

    int max_iterations = 1000;
    int iteration = 0;
    
    while (iteration < max_iterations) {
        x2 = x1 - (f(x1) * (x1 - x0)) / (f(x1) - f(x0));
        
        if (fabs(f(x2)) < tolerance) {
            return x2;
        }
        
        x0 = x1;
        x1 = x2;
        iteration++;
    }
    
    printf("Ошибка. Не найден корень.\n");
    return x2;
}