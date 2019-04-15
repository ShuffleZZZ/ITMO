package ru.ifmo.rain.glagolev.implementor;

import info.kgeorgiy.java.advanced.implementor.Impler;
import info.kgeorgiy.java.advanced.implementor.ImplerException;
import info.kgeorgiy.java.advanced.implementor.JarImpler;

import javax.tools.ToolProvider;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.lang.reflect.Parameter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.jar.Attributes;
import java.util.jar.JarEntry;
import java.util.jar.JarOutputStream;
import java.util.jar.Manifest;
import java.util.stream.Collectors;

/**
 * Generates class which is implementing given interface (not class) and collects
 * it within the given path.
 * Class has a name of the implemented interface extended by "Impl".
 * Methods of generated class return default values of return types.
 * No compilation errors expected.
 */
public class Implementor implements Impler, JarImpler {
    /**
     * Tabulation implemented with 4 spaces.
     */
    private final static String TAB = "    ";

    /**
     * Default constructor for the {@link Class}
     */
    public Implementor() {
    }

    /**
     * Main function is the program entry point, which takes the arguments from the input and
     * checks it's correctness before the launch of necessary {@link Method methods}.
     *
     * @param args Array of 2 or 3 arguments from the command line:
     *             <p>3 args case:</p>
     *             <p>args[0]: -jar tag.</p>
     *             <p>args[1]: name of interface to implement.</p>
     *             <p>args[2]: {@link Path} of implementing jar-file.</p>
     *             <p>2 args case:</p>
     *             <p>args[0]: name of interface to implement.</p>
     *             <p>args[1]: {@link Path} of implementing class.</p>
     */
    public static void main(String[] args) {
        if (args == null || args.length < 2 || args[0] == null || args[1] == null) {
            System.out.println("Input error: wrong number of arguments or illegal arguments");
            return;
        }
        boolean isJar = args[0].equals("-jar");
        if (isJar && (args.length != 3 || args[2] == null)) {
            System.out.println("Jar implementation needs more than 2 non-null arguments");
            return;
        }
        int classInd = isJar ? 1 : 0;
        try {
            Class<?> aClass = Class.forName(args[classInd]);
            if (isJar) {
                new Implementor().implementJar(aClass, Paths.get(args[classInd + 1]));
            } else {
                new Implementor().implement(aClass, Paths.get(args[classInd + 1]));
            }
        } catch (ClassNotFoundException e) {
            System.out.println("Failed to find a class: " + args[classInd]);
        } catch (InvalidPathException e) {
            System.out.println("Wrong path exception");
        } catch (ImplerException e) {
            System.out.println("Failed to implement interface: " + args[classInd]
                    + System.lineSeparator() + e.getMessage());
        }
    }

    /**
     * Function which fulfills the implementing {@link Class} by creating {@link File file's}
     * and it's {@link Method method's} structure.
     *
     * @param aClass Interface to implement.
     * @param out    {@link StringBuilder} which filling the output {@link Class}.
     * @throws IOException that might be caused by issues with writing.
     */
    private static void printClass(Class<?> aClass, StringBuilder out) throws IOException {
        if (aClass.getPackage() != null) {
            writeToBuilder("package " + aClass.getPackageName() + ';'
                    + System.lineSeparator() + System.lineSeparator(), out);
        }
        writeToBuilder("public class " + aClass.getSimpleName() + "Impl", out);
        writeToBuilder(" implements " + aClass.getSimpleName(), out);
        writeToBuilder(" {" + System.lineSeparator() + System.lineSeparator(), out);
        ArrayList<Method> methods = Arrays.stream(aClass.getMethods())
                .filter(method -> Modifier.isAbstract(method.getModifiers()))
                .collect(Collectors.toCollection(ArrayList::new));
        for (Method method : methods) {
            printMethod(method, out);
        }
        writeToBuilder("}", out);
    }

    /**
     * Writes the structure of given {@link Method} to the implementing {@link Class} with all
     * {@link Modifier modifiers}, {@link Parameter parameters} and {@link Exception exceptions}.
     * Body contains of 1 string - the return statement with default value of return type
     * (Body is empty in case of {@link Void}).
     *
     * @param method The {@link Method} given to implement
     * @param out    {@link StringBuilder} which filling the output {@link Class}class.
     */
    private static void printMethod(Method method, StringBuilder out) {
        writeToBuilder(TAB + Modifier.toString(method.getModifiers()
                & ~Modifier.ABSTRACT & ~Modifier.TRANSIENT) + ' '
                + method.getReturnType().getCanonicalName() + ' '
                + method.getName(), out);
        printParameters(method.getParameters(), out);
        printExceptions(method.getExceptionTypes(), out);
        writeToBuilder(" {", out);
        if (!method.getReturnType().equals(void.class)) {
            writeToBuilder(System.lineSeparator() + TAB + TAB + "return ", out);
            if (method.getReturnType().isPrimitive()) {
                if (method.getReturnType().equals(boolean.class)) {
                    writeToBuilder("false", out);
                } else {
                    writeToBuilder("0", out);
                }
            } else {
                writeToBuilder("null", out);
            }
            writeToBuilder(';' + System.lineSeparator() + TAB, out);
        }
        writeToBuilder('}' + System.lineSeparator() + System.lineSeparator(), out);
    }

    /**
     * Function prints the parameters of {@link Method} (or Constructor)
     * into given {@link StringBuilder}.
     *
     * @param parameters  Array of parameters of the function.
     * @param out        {@link StringBuilder} which filling the output {@link Class}.
     */
    private static void printParameters(Parameter[] parameters, StringBuilder out) {
        writeToBuilder("(", out);
        if (parameters.length != 0) {
            int last = parameters.length - 1;
            for (int i = 0; i < last; ++i) {
                writeToBuilder(parameters[i].getType().getCanonicalName() + " arg" + i + ", ", out);
            }
            writeToBuilder(parameters[last].getType().getCanonicalName() + " arg" + last, out);
        }
        writeToBuilder(")", out);
    }

    /**
     * Function prints the {@link Exception exceptions} of {@link Method} (or Constructor)
     * into given {@link StringBuilder}, if any exist.
     *
     * @param exceptions {@link java.lang.reflect.Array} of {@link Exception exceptions} the function throws.
     * @param out        {@link StringBuilder} which filling the output {@link Class}.
     */
    private static void printExceptions(Class[] exceptions, StringBuilder out) {
        if (exceptions.length == 0) {
            return;
        }
        writeToBuilder(" throws ", out);
        int last = exceptions.length - 1;
        for (int i = 0; i < last; ++i) {
            writeToBuilder(exceptions[i].getName() + ", ", out);
        }
        writeToBuilder(exceptions[last].getName(), out);
    }

    /**
     * Appends given {@link String} to the given {@link StringBuilder} in UTF-8 supportive format.
     *
     * @param s   {@link String} to put to builder.
     * @param out given {@link StringBuilder}.
     */
    private static void writeToBuilder(String s, StringBuilder out) {
        for (char c : s.toCharArray()) {
            out.append(c < 128 ? Character.toString(c) : String.format("\\u%04x", (int) c));
        }
    }

    /**
     * Creates a jar-file with implementation of interface at the given {@link Path}.
     *
     * @param jarFile   Name of .jar file.
     * @param classFile {@link Path} to the compiled {@link Class} for archivation.
     */
    private static void createJar(Path jarFile, String classFile) {
        Manifest manifest = new Manifest();
        manifest.getMainAttributes().put(Attributes.Name.MANIFEST_VERSION, "1.0");
        try (JarOutputStream jarOutputStream = new JarOutputStream(new FileOutputStream(jarFile.toFile()), manifest)) {
            jarOutputStream.putNextEntry(new JarEntry(classFile));
            Files.copy(Paths.get(classFile), jarOutputStream);
        } catch (IOException e) {
            System.out.println("Jar writing exception: " + e.getMessage());
        }
    }

    /**
     * Makes an implementation of given interface and puts it into class-file at given {@link Path}.
     *
     * @param aClass Interface to implement.
     * @param path   {@link Path} to create implementing class at.
     * @throws ImplerException which points out wrong input data.
     */
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
                try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFile), StandardCharsets.UTF_8)) {
                    StringBuilder out = new StringBuilder();
                    printClass(aClass, out);
                    writer.write(out.toString());
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

    /**
     * Makes an implementation of given interface and packs it to the Jar-file at given {@link Path}.
     *
     * @param aClass Interface to implement.
     * @param path   {@link Path} for created jar-file.
     * @throws ImplerException which points out wrong input data or compilation error.
     */
    @Override
    public void implementJar(Class<?> aClass, Path path) throws ImplerException {
        Path root = Paths.get(".");
        implement(aClass, root);
        String outputPath = aClass.getName().replace(".", "/") + "Impl";
        var compiler = ToolProvider.getSystemJavaCompiler();
        if (compiler == null) {
            throw new ImplerException("Null compiler received");
        }
        String[] args = {outputPath + ".java", "-encoding", "cp866", "-cp", System.getProperty("java.class.path")};
        int compileResult = compiler.run(null, null, null, args);
        if (compileResult != 0) {
            throw new ImplerException("Compilation error, returned: " + compileResult);
        }
        createJar(path, outputPath + ".class");
    }
}
