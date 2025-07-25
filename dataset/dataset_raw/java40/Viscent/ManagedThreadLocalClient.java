/*
授权声明：
本源码系《Java多线程编程实战指南（设计模式篇）》一书（ISBN：978-1-7-121-27006-2，以下称之为“原书”）的配套源码，
欲了解本代码的更多细节，请参考原书。
本代码仅为原书的配套说明之用，并不附带任何承诺（如质量保证和收益）。
以任何形式将本代码之部分或者全部用于营利性用途需经版权人书面同意。
将本代码之部分或者全部用于非营利性用途需要在代码中保留本声明。
任何对本代码的修改需在代码中以注释的形式注明修改人、修改时间以及修改内容。
本代码可以从下URL下载：
https://github.com/Viscent/javamtp
http://www.broadview.com.cn/27006
*/

package io.github.viscent.mtpattern.ch10.tss.example;

//import io.github.viscent.mtpattern.tss.InitialValueProvider;
import io.github.viscent.mtpattern.ch10.tss.ManagedThreadLocal;

public class ManagedThreadLocalClient {
    private final static ManagedThreadLocal<Integer> mtl = ManagedThreadLocal
        .newInstance(new ManagedThreadLocal.InitialValueProvider<Integer>() {
            
            @Override
            protected Integer initialValue() {
                System.out.println(Thread.currentThread().getName());
                return Integer.valueOf((int) Thread.currentThread().getId());
            }

        });

    public static void main(String[] args) {
        for (int i = 0; i < 3; i++) {
            new Helper().start();
        }

    }

    static class Helper extends Thread {

        @Override
        public void run() {

            System.out.println(mtl.get());
        }

    }

}
