import java.io.*;
import java.util.InputMismatchException;

/**
 * Created by Shreyans Sheth [bholagabbar] on 9/13/2015 at 3:09 PM using IntelliJ IDEA (Fast IO Template)
 */

class MGCH3D_15
{
    public static void main(String[] args) throws Exception
    {
        //System.setIn(new FileInputStream("E:/Shreyans/Documents/Code/CODE/src/Stdin_File_Read.txt"));
        InputReader in = new InputReader(System.in);
        OutputWriter out = new OutputWriter(System.out);
        double n=in.readDouble();
        int q=in.readInt();
        double []x=new double[(int)n];
        double []y=new double[(int)n];
        double []z=new double[(int)n];
        for(int i=0;i<n;i++)
        {
            x[i]=in.readDouble();
            y[i]=in.readDouble();
            z[i]=in.readDouble();
        }
        double p1[][]=new double [(int)n+1][(int)n+1];
        double p2[][]=new double [(int)n+1][(int)n+1];
        double p3[][]=new double [(int)n+1][(int)n+1];
        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                p1[i][j]=Math.pow(x[i]-x[j],4);
                p1[j][i]=p1[i][j];
                p2[i][j]=Math.pow(y[i]-y[j],4);
                p2[j][i]=p2[i][j];
                p3[i][j]=Math.pow(z[i]-z[j],4);
                p3[j][i]=p3[i][j];
            }
        }
        for(int i1=0;i1<q;i1++)
        {
            double a=in.readDouble(),b=in.readDouble(),c=in.readDouble(),d=in.readDouble();
            double ans=0;
            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)
                    if(i!=j)
                        ans+=Math.abs(a*(x[i]-x[j])+b*(y[i]-y[j])+c*(z[i]-z[j])+d)/((n*(n-1))*Math.sqrt(p1[i][j]+p2[i][j]+p3[i][j]));
            out.printLine(ans);
        }
    }

    //FAST IO
    private static class InputReader
    {
        private InputStream stream;
        private byte[] buf = new byte[1024];
        private int curChar;
        private int numChars;
        private SpaceCharFilter filter;

        public InputReader(InputStream stream)
        {
            this.stream = stream;
        }

        public int read()
        {
            if (numChars == -1)
                throw new InputMismatchException();
            if (curChar >= numChars)
            {
                curChar = 0;
                try
                {
                    numChars = stream.read(buf);
                } catch (IOException e)
                {
                    throw new InputMismatchException();
                }
                if (numChars <= 0)
                    return -1;
            }
            return buf[curChar++];
        }

        public int readInt()
        {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            int sgn = 1;
            if (c == '-')
            {
                sgn = -1;
                c = read();
            }
            int res = 0;
            do
            {
                if (c < '0' || c > '9')
                    throw new InputMismatchException();
                res *= 10;
                res += c - '0';
                c = read();
            } while (!isSpaceChar(c));
            return res * sgn;
        }

        public String readString()
        {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            StringBuilder res = new StringBuilder();
            do
            {
                res.appendCodePoint(c);
                c = read();
            } while (!isSpaceChar(c));
            return res.toString();
        }

        public double readDouble()
        {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            int sgn = 1;
            if (c == '-')
            {
                sgn = -1;
                c = read();
            }
            double res = 0;
            while (!isSpaceChar(c) && c != '.')
            {
                if (c == 'e' || c == 'E')
                    return res * Math.pow(10, readInt());
                if (c < '0' || c > '9')
                    throw new InputMismatchException();
                res *= 10;
                res += c - '0';
                c = read();
            }
            if (c == '.')
            {
                c = read();
                double m = 1;
                while (!isSpaceChar(c))
                {
                    if (c == 'e' || c == 'E')
                        return res * Math.pow(10, readInt());
                    if (c < '0' || c > '9')
                        throw new InputMismatchException();
                    m /= 10;
                    res += (c - '0') * m;
                    c = read();
                }
            }
            return res * sgn;
        }

        public boolean isSpaceChar(int c)
        {
            if (filter != null)
                return filter.isSpaceChar(c);
            return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
        }

        public String next()
        {
            return readString();
        }

        public interface SpaceCharFilter
        {
            public boolean isSpaceChar(int ch);
        }
    }

    private static class OutputWriter
    {
        private final PrintWriter writer;

        public OutputWriter(OutputStream outputStream)
        {
            writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream)));
        }

        public OutputWriter(Writer writer)
        {
            this.writer = new PrintWriter(writer);
        }

        public void print(Object... objects)
        {
            for (int i = 0; i < objects.length; i++)
            {
                if (i != 0)
                    writer.print(' ');
                writer.print(objects[i]);
            }
            writer.flush();
        }

        public void printLine(Object... objects)
        {
            print(objects);
            writer.println();
            writer.flush();
        }

        public void close()
        {
            writer.close();
        }

        public void flush()
        {
            writer.flush();
        }
    }
}