package ru.ifmo.rain.glagolev.student;

import info.kgeorgiy.java.advanced.student.Student;
import info.kgeorgiy.java.advanced.student.StudentQuery;


import java.util.*;
import java.util.function.BinaryOperator;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public class StudentDB implements StudentQuery {
    @Override
    public List<String> getFirstNames(List<Student> list) {
        return getField(list, Student::getFirstName);
    }

    @Override
    public List<String> getLastNames(List<Student> list) {
        return getField(list, Student::getLastName);
    }

    @Override
    public List<String> getGroups(List<Student> list) {
        return getField(list, Student::getGroup);
    }

    @Override
    public List<String> getFullNames(List<Student> list) {
        return getField(list, student ->
                String.join(" ", student.getFirstName(), student.getLastName()));
    }

    private List<String> getField(List<Student> list, Function<Student, String> function) {
        return list.stream().map(function).collect(Collectors.toList());
    }

    @Override
    public Set<String> getDistinctFirstNames(List<Student> list) {
        return list.stream()
                .map(Student::getFirstName)
                .collect(Collectors.toCollection(TreeSet::new));
    }

    @Override
    public String getMinStudentFirstName(List<Student> list) {
        return list.stream()
                .min(Student::compareTo)
                .map(Student::getFirstName)
                .orElse("");
    }

    @Override
    public List<Student> sortStudentsById(Collection<Student> collection) {
        return sortStudentsByField(collection, Student::compareTo);
    }

    @Override
    public List<Student> sortStudentsByName(Collection<Student> collection) {
        return sortStudentsByField(collection, Comparator
                .comparing(Student::getLastName, String::compareTo)
                .thenComparing(Student::getFirstName, String::compareTo)
                .thenComparingInt(Student::getId));
    }

    private List<Student> sortStudentsByField(Collection<Student> collection, Comparator<Student> comparator) {
        return collection.stream().sorted(comparator).collect(Collectors.toList());
    }

    @Override
    public List<Student> findStudentsByFirstName(Collection<Student> collection, String s) {
        return findStudentsByField(collection,
                student -> student.getFirstName().equals(s));
    }

    @Override
    public List<Student> findStudentsByLastName(Collection<Student> collection, String s) {
        return findStudentsByField(collection,
                student -> student.getLastName().equals(s));
    }

    @Override
    public List<Student> findStudentsByGroup(Collection<Student> collection, String s) {
        return findStudentsByField(collection,
                student -> student.getGroup().equals(s));
    }

    private List<Student> findStudentsByField(Collection<Student> collection, Predicate<Student> predicate) {
        return sortStudentsByName(collection.stream().filter(predicate).collect(Collectors.toList()));
    }

    @Override
    public Map<String, String> findStudentNamesByGroup(Collection<Student> collection, String s) {
        return collection.stream()
                .filter(student -> student.getGroup().equals(s))
                .collect(Collectors.toMap(Student::getLastName, Student::getFirstName,
                        BinaryOperator.minBy(Comparator.naturalOrder())));
    }
}
