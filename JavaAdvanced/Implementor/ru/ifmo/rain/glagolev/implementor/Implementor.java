package ru.ifmo.rain.glagolev.implementor;

import info.kgeorgiy.java.advanced.implementor.Impler;
import info.kgeorgiy.java.advanced.implementor.ImplerException;

import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.lang.reflect.Parameter;
import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.stream.Collectors;

public class Implementor implements Impler {

    private final static String TAB = "    ";

    public static void main(String[] args) {
        if (args == null || args.length != 2 || args[0] == null || args[1] == null) {
            System.out.println("Input error: wrong number of arguments or illegal arguments");
            return;
        }
        try {
            Class<?> aClass = Class.forName(args[0]);
            new Implementor().implement(aClass, Paths.get(args[1]));
        } catch (ClassNotFoundException e) {
            System.out.println("Failed to find a class: " + args[0]);
        } catch (InvalidPathException e) {
            System.out.println("Wrong path exception");
        } catch (ImplerException e) {
            System.out.println("Failed to implement interface: " + args[0]
                    + System.lineSeparator() + e.getMessage());
        }
    }

    private static void printClass(Class<?> aClass, BufferedWriter out) throws IOException {
        if (aClass.getPackage() != null) {
            out.write("package " + aClass.getPackageName() + ';'
                    + System.lineSeparator() + System.lineSeparator());
        }
        out.write("public class " + aClass.getSimpleName() + "Impl");
        out.write(" implements " + aClass.getSimpleName());
        out.write(" {" + System.lineSeparator() + System.lineSeparator());
        ArrayList<Method> methods = Arrays.stream(aClass.getMethods())
                .filter(method -> Modifier.isAbstract(method.getModifiers()))
                .collect(Collectors.toCollection(ArrayList::new));
        for (Method method : methods) {
            printMethod(method, out);
        }
        out.write('}');
    }

    private static void printMethod(Method method, BufferedWriter out) throws IOException {
        out.write(TAB + Modifier.toString(method.getModifiers()
                & ~Modifier.ABSTRACT & ~Modifier.TRANSIENT) + ' '
                + method.getReturnType().getCanonicalName() + ' '
                + method.getName());
        printParameters(method.getParameters(), out);
        printExceptions(method.getExceptionTypes(), out);
        out.write(" {");
        if (!method.getReturnType().equals(void.class)) {
            out.write(System.lineSeparator() + TAB + TAB + "return ");
            if (method.getReturnType().isPrimitive()) {
                if (method.getReturnType().equals(boolean.class)) {
                    out.write("false");
                } else {
                    out.write('0');
                }
            } else {
                out.write("null");
            }
            out.write(';' + System.lineSeparator() + TAB);
        }
        out.write('}' + System.lineSeparator() + System.lineSeparator());
    }

    private static void printParameters(Parameter[] parameters, BufferedWriter out) throws IOException {
        out.write('(');
        if (parameters.length != 0) {
            int last = parameters.length - 1;
            for (int i = 0; i < last; ++i) {
                out.write(parameters[i].getType().getCanonicalName() + " arg" + i + ", ");
            }
            out.write(parameters[last].getType().getCanonicalName() + " arg" + last);
        }
        out.write(')');
    }

    private static void printExceptions(Class[] exceptions, BufferedWriter out) throws IOException {
        if (exceptions.length == 0) {
            return;
        }
        out.write(" throws ");
        int last = exceptions.length - 1;
        for (int i = 0; i < last; ++i) {
            out.write(exceptions[i].getName() + ", ");
        }
        out.write(exceptions[last].getName());
    }

    @Override
    public void implement(Class<?> aClass, Path path) throws ImplerException {
        if (Modifier.isFinal(aClass.getModifiers()) || aClass.isEnum()) {
            throw new ImplerException("Given class cannot be implemented");
        }
        if (aClass.isInterface()) {
            String classPackage = aClass.getPackageName();
            String outputPath = path.toString() + File.separator
                    + classPackage.replace(".", File.separator);
            try {
                Files.createDirectories(Paths.get(outputPath));
                String outputFile = outputPath + File.separator
                        + aClass.getSimpleName() + "Impl.java";
                try (BufferedWriter out = Files.newBufferedWriter(Paths.get(outputFile))) {
                    printClass(aClass, out);
                } catch (IOException e) {
                    throw new ImplerException("Output write exception: ", e);
                }
            } catch (IOException e) {
                throw new ImplerException("Output path exception: ", e);
            }
        } else {
            throw new ImplerException("Input error: Implements interfaces only");
        }
    }
}
