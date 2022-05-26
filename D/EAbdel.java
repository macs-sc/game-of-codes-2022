import java.util.*;
import java.io.*;

public class EAbdel {
	public static final String INPUT_FILE = "groups.in";
	public static void main(String[] args) throws Exception {
		Scanner in = new Scanner(System.in);
		int t = in.nextInt();
		while(t-->0) {
			char[] arr = in.next().toCharArray();
			int[] cnt = new int[26];

			if(arr.length == 1) { // base case to avoid RTE
				System.out.println(1);
				continue;
			}

			for(char c : arr) {
				if(c>= 'a' && c <= 'z')
					++cnt[c - 'a'];
			}

			for(int i = 0; i < arr.length; ++i) {
				if(arr[i] != '.') continue;
				int j = 0;
				int k = 0;
				for(j = 0; j < 26; ++j) {
					if(i == 0) {

						if(arr[i + 1] - 'a' != j && cnt[j] > 0) 
							break;
						else if(arr[i + 1] - 'a' != j) {
							k = j;
						}
					
					} else if(i == arr.length - 1) {

						if(arr[i - 1] - 'a' != j && cnt[j] > 0) 
							break;
						else if(arr[i - 1] - 'a' != j) 
							k = j;
						
					} else{

						if(arr[i - 1] - 'a' != j && arr[i + 1] - 'a' != j && cnt[j] > 0)
							break;
						else if(arr[i - 1] - 'a' != j && arr[i + 1] - 'a' != j) 
							k = j;
						
					}
				}

				if(j == 26) j = k;
				
				++cnt[j];
				arr[i] = (char) ('a' + j);

			}


			int ans = 0;
			for(int c : cnt) {
				if(c > 0) ++ans;
			} 

			for(int i = 1; i < arr.length && ans >= 0; ++i) {
				if(arr[i] == arr[i - 1])  {
					ans = -1;
				}
			}


			System.out.println(ans);
		}
	}
}