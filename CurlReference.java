import java.util.Arrays;
public class CurlReference {

    public static void main(String[] args){
        CurlReference CurlReference = new CurlReference();
        int[] input = new int[243];
        //System.out.println(args[0]);
        for(int i=0; i<243; i++){
            input[i] = Integer.parseInt(args[0]);
        }
        int[] output = new int[243];
        CurlReference.absorb(input, 0, 243);
        CurlReference.squeeze(output, 0);
        System.out.println(Arrays.toString(output));
        //System.out.println("\nLength: " + output.length);

    }
    public static final int HASH_SIZE = 243;
    public static final int STATE_SIZE = 3 * HASH_SIZE;
    public static final int[] T = {
        1,
        0,
        -1,
        0,
        1,
        -1,
        0,
        0,
        -1,
        1,
        0
    }; // {1, 0, -1, 1, -1, 0, -1, 1, 0};
    public static final int[] INDICES = new int[STATE_SIZE + 1];

    static {

        for (int i = 0; i < STATE_SIZE; i++) {

            INDICES[i + 1] = INDICES[i] + (INDICES[i] < 365 ? 364 : -365);
        }
    }

    public final int[] state = new int[STATE_SIZE], stateCopy = new int[STATE_SIZE];


    void reset() {

        for (int i = 0; i < state.length; i++) {

            state[i] = 0;
        }
    }

    public void absorb(final int[] input, int offset, int size) {

        do {

            System.arraycopy(input, offset, state, 0, size < HASH_SIZE ? size : HASH_SIZE);
            transform();
            offset += HASH_SIZE;

        } while ((size -= HASH_SIZE) > 0);
    }

    public void squeeze(final int[] output, final int offset) {

        System.arraycopy(state, 0, output, offset, HASH_SIZE);
        transform();
    }

    public void transform() {

        for (int r = 27; r-- > 0;) {

            System.arraycopy(state, 0, stateCopy, 0, STATE_SIZE);

            for (int i = 0; i < STATE_SIZE;) {

                state[i] = T[stateCopy[INDICES[i]] + (stateCopy[INDICES[++i]] << 2) + 5];
            }
        }
    }
}
